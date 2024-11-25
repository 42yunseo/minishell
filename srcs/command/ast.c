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

#include <stdio.h>

t_cmd	*make_cmd(t_list *token_list)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	while (token_list != NULL && ((t_token *)token_list)->type != w_pipe)
	{
		token = token_list->content;
		if (token->type == w_word)
		{
			ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup(token->word)));
		}
		// else
		// {
		// 	ft_lstadd_back(&cmd->redirects, ft_lstnew(make_redirection(token)));

		// }
		token_list = token_list->next;
	}
	return (cmd);
}

t_ast_node	*parse_cmd(t_list *token_list)
{
	t_ast_node	*node;

	node = ft_new_ast_node(make_cmd(token_list), node_cmd);
	if (node == NULL)
		return (NULL);
	return (node);
}

void	make_ast(t_list *token_list)
{
	t_ast		*ast;
	t_ast_node	*node;
	//t_token		*token;

	ast = ft_astnew();
	set_global_command(ast);
	while (token_list != NULL)
	{
		// token = token_list->content;
		// if (token->type != w_pipe)
		// {

		// }

		node = parse_cmd(token_list);
		if (node != NULL)
			ast->root = node;
		while (token_list && ((t_token *)(token_list))->type != w_pipe)
			token_list = token_list->next;
		if (token_list && ((t_token *)(token_list))->type != w_pipe)
		{
			/* parse pipe logic */
			// node = pasre_pipe(token);
			token_list = token_list->next;
			continue;
		}
	}
}

