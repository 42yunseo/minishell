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

// int	execute_cmd(t_cmd *cmd)
// {
// 	int		result;
// 	int		original_fd[2];
// 	t_list	*ptr;

// 	result = 0;
// 	original_fd[STDIN_FILENO] = dup(STDIN_FILENO);
// 	original_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
// 	result = execute_redirect(cmd->redirects);
// 	ptr = cmd->args;
// 	while (result == 0 && ptr != NULL)
// 	{
// 		if (*(char *)ptr->content == '\0')
// 			ptr = ptr->next;
// 		else
// 		{
// 			if (isabuiltin(ptr))
// 				result = execute_builtin(ptr);
// 			else
// 				result = execute_simple(ptr);
// 		}
// 	}
// 	dup2(original_fd[STDIN_FILENO], STDIN_FILENO);
// 	dup2(original_fd[STDOUT_FILENO], STDOUT_FILENO);
// 	close(original_fd[STDIN_FILENO]);
// 	close(original_fd[STDOUT_FILENO]);
// 	return (result);
// }

int	execute_node(t_ast_node *node)
{
	int	exit_status;

	exit_status = 0;
	if (node->type == node_cmd && node->u_value.cmd != NULL)
		exit_status = execute_cmd(node->u_value.cmd);
	if (node->type == node_pipe && node->u_value.pipe != NULL)
		exit_status = execute_pipe(node->u_value.pipe);
	//printf("execute_node status : %d\n", exit_status);
	return (exit_status);
}

int	execute_command(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast->root == NULL)
		return (0);
	ast->last_exit_status = execute_node(ast->root);
	//printf("exeucte_command status : %d\n", ast->last_exit_status);
	return (ast->last_exit_status);
}
