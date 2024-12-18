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

int	execute_cmd(t_cmd *cmd)
{
	int		result;
	int		original_fd[2];

	result = 0;
	original_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	original_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	result = execute_redirect(cmd->redirects);
	if (result == 0 && cmd->args != NULL)
	{
		if (isabuiltin(cmd->args))
			result = execute_builtin(cmd->args);
		else
			result = execute_simple(cmd->args);
	}
	dup2(original_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(original_fd[STDOUT_FILENO], STDOUT_FILENO);
	close(original_fd[STDIN_FILENO]);
	close(original_fd[STDOUT_FILENO]);
	return (result);
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
		return (0);
	if (ast->root == NULL)
		return (0);
	ast->last_exit_status = execute_node(ast->root);
	return (ast->last_exit_status);
}
