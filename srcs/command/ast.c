/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:11:19 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/19 15:11:20 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_ast	*ft_astnew(void)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	ft_memset(ast, 0, sizeof(t_ast));
	return (ast);
}

t_ast_node	*ft_new_ast_node(void *value, enum e_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	if (type == node_cmd)
		node->u_value.cmd = (t_cmd *)value;
	if (type == node_pipe)
		node->u_value.pipe = (t_pipe *)value;
	return (node);
}

void	make_ast(t_list *token_list)
{
	t_ast		*ast;
	t_ast_node	*node;

	ast = ft_astnew();
	set_global_command(ast);
	node = parse_node(token_list);
	ast->root = node;
}
