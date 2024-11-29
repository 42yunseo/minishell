/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:51:40 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/22 12:51:41 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "my_signal.h"
#include "env.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void	execute_child(char **argv, char *cmd_path, char **envp)
{
	struct stat	stat_buf;

	if (access(cmd_path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (cmd_path == NULL)
		{
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		else
			perror(*argv);
		exit (127);
	}
	set_signals(SIG_DEFAULT, SIG_DEFAULT);
	execve(cmd_path, argv, envp);
	stat(cmd_path, &stat_buf);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (S_ISDIR(stat_buf.st_mode))
		ft_putendl_fd(strerror(EISDIR), STDERR_FILENO);
	else if (access(cmd_path, X_OK) == -1)
		ft_putendl_fd(strerror(EACCES), STDERR_FILENO);
	exit(126);
}

int	execute_parent(pid_t pid)
{
	int	status;
	int	result;
	int	signo;

	set_signals(SIG_CHILD, SIG_CHILD);
	result = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		result = (128 + signo);
	}
	else if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	set_signals(SIG_SHELL, SIG_IGNORE);
	return (result);
}

char	*find_cmd_path(const char *cmd)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	char	*tmp;

	paths = ft_split(ft_getenv("PATH"), ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i++], cmd_path);
		if (access(tmp, X_OK) != -1)
		{
			free(cmd_path);
			free_argv(paths);
			return (tmp);
		}
		free(tmp);
	}
	free(cmd_path);
	free_argv(paths);
	return (NULL);
}

char	*get_cmd_path(const char *cmd)
{
	char	*cmd_path;

	if (ft_strchr(cmd, '/') != NULL && access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') != NULL)
		cmd_path = ft_strdup(cmd);
	else
		cmd_path = find_cmd_path(cmd);
	return (cmd_path);
}

int	execute_simple(t_list *args)
{
	pid_t	pid;
	int		result;
	char	**argv;
	char	*cmd_path;
	char	**envp;

	result = 0;
	cmd_path = get_cmd_path(args->content);
	argv = list_to_argv(args);
	envp = list_to_envp(*get_envp());
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		execute_child(argv, cmd_path, envp);
	result = execute_parent(pid);
	if (cmd_path != NULL)
		free(cmd_path);
	free_argv(argv);
	free_argv(envp);
	return (result);
}
