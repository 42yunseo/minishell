/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:11:38 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/23 19:11:40 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void	execute_pipe_child(int pipe_fd[2], t_ast_node *node, int mode)
{
	int	status;

	close(pipe_fd[1 - mode]);
	dup2(pipe_fd[mode], mode);
	close(pipe_fd[mode]);
	if (node->type == node_cmd)
		status = execute_cmd(node->u_value.cmd);
	if (node->type == node_pipe)
		status = execute_pipe(node->u_value.pipe);
	exit (status);
}

int	execute_pipe_parent(pid_t pid[2])
{
	int	status;
	int	signo;
	int	result;

	result = 0;
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		result = (128 + signo);
	}
	else if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	return (result);
}

int	execute_pipe(t_pipe *pipe_node)
{
	int		exit_status;
	int		pipe_fd[2];
	pid_t	pid[2];

	exit_status = 0;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (-1);
	if (pid[0] == 0)
		execute_pipe_child(pipe_fd, pipe_node->l_node, 1);
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
	{
		kill(pid[0], SIGKILL);
		return (-1);
	}
	if (pid[1] == 0)
		execute_pipe_child(pipe_fd, pipe_node->r_node, 0);
	close(pipe_fd[0]);
	exit_status = execute_pipe_parent(pid);
	return (exit_status);
}
