/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:31:21 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/08 17:31:22 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_cmd	*tokens_to_cmd(t_list *token_list)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_cmd_new();
	token = token_list->content;
	while (token_list != NULL)
	{
		if (token->type >= w_input_redirect && token->type <= w_append)
			if (make_redir(token->type, token_list->next) != 0)
	}
	return (cmd);
}

void	make_cmd(t_list *token_list)
{
	t_list	*cmd_list;
	t_cmd	*cur_cmd;
	t_token	*token;

	cmd_list = NULL;
	cur_cmd = NULL;
	while (token_list != NULL)
	{
		cur_cmd = tokens_to_cmd(token_list);
		if (cur_cmd == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&cmd_list, ft_lstnew(cur_cmd));
		token = token_list->content;
		while (token->type != NULL && token->type != pipe)
			token_list = token_list->next;
		if (token->type == pipe)
			token_list = token_list->next;
	}
	set_global_command(cmd_list);
}
