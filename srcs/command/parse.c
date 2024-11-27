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
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == w_pipe)
			break ;
		token_list = token_list->next;
	}
	if (token_list != NULL && token->type == w_pipe)
		node = parse_pipe(node, token_list);
	return (node);
}

t_cmd	*make_cmd(t_list *token_list)
{
	t_cmd		*cmd;
	t_token		*token;
	t_redirect	*redirection;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == w_pipe)
			break ;
		if (token->type == w_word)
			ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup(token->word)));
		else
		{
			redirection = make_redirection(token_list);
			ft_lstadd_back(&cmd->redirects, ft_lstnew(redirection));
			token_list = token_list->next;
		}
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

t_pipe	*make_pipe(t_ast_node *l_node, t_list *token_list)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)malloc(sizeof(t_pipe));
	if (pipe_node == NULL)
		return (NULL);
	ft_memset(pipe_node, 0, sizeof(t_pipe));
	pipe_node->l_node = l_node;
	pipe_node->r_node = parse_node(token_list->next);
	return (pipe_node);
}

t_ast_node	*parse_pipe(t_ast_node *l_node, t_list *token_list)
{
	t_ast_node	*node;

	node = ft_new_ast_node(make_pipe(l_node, token_list), node_pipe);
	if (node == NULL)
		return (NULL);
	return (node);
}
