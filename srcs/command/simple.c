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

void	execute_child(char **argv, char *cmd_path)
{
	char	*cmd;

	set_signals(SIG_DEFAULT, SIG_DEFAULT);
	cmd = *argv;
	execve(cmd_path, argv, *get_envp());
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

int	execute_parent(int pid)
{
	int	status;
	int	result;

	result = 0;
	waitpid(pid, &status, 0);
	result = WEXITSTATUS(status);
	ft_putendl_fd(ft_itoa(result), 2);
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
		return (cmd);
	i = 0;
	paths = ft_split(ft_getenv("PATH"), ':');
	cmd_path = ft_strjoin("/", cmd);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], cmd_path);
		if (access(tmp, X_OK) != -1)
		{
			free(cmd_path);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_args(paths);
	return (cmd_path);
}

int	execute_simple(t_list *args)
{
	pid_t	pid;
	int		result;
	char	**argv;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	argv = list_to_argv(args);
	cmd_path = get_cmd_path(*argv);
	if (pid == 0)
		execute_child(argv, cmd_path);
	else
		result = execute_parent(pid);
	free_args(argv);
	if (cmd_path != NULL)
		free(cmd_path);
	return (result);
}
