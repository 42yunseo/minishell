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
#include <sys/wait.h>

#include <stdio.h>

void	execute_child(char **argv, char *cmd_path, char **envp)
{
	char	*cmd;

	set_signals(SIG_DEFAULT, SIG_DEFAULT);
	cmd = *argv;
	execve(cmd_path, argv, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
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

char	**list_to_argv(t_list *list)
{
	char	**argv;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(list);
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		argv[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	argv[len] = NULL;
	return (argv);
}

char	*get_cmd_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	if (access(cmd, X_OK) != -1)
		return (NULL);
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
			cmd_path = tmp;
			break ;
		}
		free(tmp);
	}
	free_argv(paths);
	return (cmd_path);
}

int	execute_simple(t_list *args)
{
	// printf("call simple\n");
	pid_t	pid;
	int		result;
	char	**argv;
	char	*cmd_path;
	char	**envp;

	result = 0;
	argv = list_to_argv(args);
	envp = list_to_envp(*get_envp());
	cmd_path = get_cmd_path(*argv);
	if (cmd_path == NULL)
		cmd_path = ft_strdup(*argv);
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
