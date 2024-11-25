/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:04:13 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/26 00:04:14 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	dispose_ast_node(t_ast_node *node);

void	dispose_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ft_lstclear(&cmd->args, free);
	ft_lstclear(&cmd->redirects, free_redirection);
	free(cmd);
	cmd = NULL;
}

void	dispose_pipe(t_pipe *pipe_node)
{
	dispose_ast_node(pipe_node->l_node);
	dispose_ast_node(pipe_node->r_node);
	free(pipe_node);
	pipe_node = NULL;
}

void	dispose_ast_node(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == node_cmd)
		dispose_cmd(node->u_value.cmd);
	if (node->type == node_pipe)
		dispose_pipe(node->u_value.pipe);
	free(node);
}

void	dispose_command(void)
{
	t_ast	*ast;

	ast = *get_global_command();
	if (ast == NULL)
		return ;
	dispose_ast_node(ast->root);
	free(ast);
}
