/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:15:33 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/08 22:15:34 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "builtin.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int	execute_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	cmd->origin_stdin = dup(STDIN_FILENO);
	cmd->origin_stdout = dup(STDOUT_FILENO);
	//result = execute_redirect(cmd->redirects);
	if (result == 0 && cmd->args != NULL)
	{
		if (isabuiltin(cmd->args))
			result = execute_builtin(cmd->args);
		else
			result = execute_simple(cmd->args);
	}
	dup2(cmd->origin_stdin, STDIN_FILENO);
	dup2(cmd->origin_stdout, STDOUT_FILENO);
	close(cmd->origin_stdin);
	close(cmd->origin_stdout);
	return (result);
}

void	execute_pipe_child(int pipe_fd[2], t_ast_node *node, int mode)
{
	int	status;

	close(pipe_fd[1 - mode]);
	dup2(pipe_fd[mode], mode);
	status = execute_node(node);
	close(pipe_fd[mode]);
	exit (status);
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
	pid[1] = fork();
	if (pid[1] == -1)
	{
		kill(pid[0], SIGKILL);
		return (-1);
	}
	if (pid[1] == 0)
		execute_pipe_child(pipe_fd, pipe_node->r_node, 0);
	wait(&exit_status);
	wait(&exit_status);
	return (exit_status);
}

int	execute_node(t_ast_node *node)
{
	int	exit_status;

	exit_status = 0;
	if (node->type == node_cmd && node->u_value.cmd != NULL)
		exit_status = execute_cmd(node->u_value.cmd);
	if (node->type == node_pipe && node->u_value.pipe != NULL)
		exit_status = execute_pipe(node->u_value.pipe);
	return (exit_status);
}

int	execute_command(t_ast *ast)
{
	if (ast == NULL)
		return (-1);
	if (ast->root == NULL)
		return (-1);
	ast->last_exit_status = execute_node(ast->root);
	return (ast->last_exit_status);
}
