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

#include <stdio.h>

int	execute_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	cmd->origin_stdin = dup(STDIN_FILENO);
	cmd->origin_stdout = dup(STDOUT_FILENO);
	result = execute_redirect(cmd->redirects);
	//printf("redirect result : %d\n", result);
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
	//printf("Exit status : %d\n", result);
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
		return (-1);
	if (ast->root == NULL)
		return (-1);
	ast->last_exit_status = execute_node(ast->root);
	return (ast->last_exit_status);
}