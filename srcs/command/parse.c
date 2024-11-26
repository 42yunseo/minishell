/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:11:19 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/26 22:59:04 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

t_ast_node	*parse_node(t_list *token_list)
{
	t_ast_node	*node;
	t_token		*token;

	if (token_list == NULL)
		return (NULL);
	node = parse_cmd(token_list);
	token = token_list->content;
	while (token_list != NULL && ((t_token *)(token_list->content))->type != w_pipe)
	{
		token_list = token_list->next;
	}
	if (token_list && token && ((t_token *)(token_list->content))->type == w_pipe)
		node = parse_pipe(node, token_list);
	return (node);
}

t_ast_node	*parse_cmd(t_list *token_list)
{
	t_ast_node	*node;

	node = ft_new_ast_node(make_cmd(token_list), node_cmd);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_ast_node	*parse_pipe(t_ast_node *l_node, t_list *token_list)
{
	t_ast_node	*node;
	t_pipe		*pipe_node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	pipe_node = (t_pipe *)malloc(sizeof(t_pipe));
	if (pipe_node == NULL)
		return (NULL);
	pipe_node->l_node = l_node;
	pipe_node->r_node = parse_node(token_list->next);
	node->type = node_pipe;
	node->u_value.pipe = pipe_node;
	return (node);
}
