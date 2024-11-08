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

void	token_to_cmd(t_token *token, t_cmd *cmd)
{
	static enum e_word_type	before_type;

	if (token->type == w_input_redirect)
		ft_lstadd_back(&cmd->redirects, ft_lstnew());
	if (token->type == w_output_redirect)
	if (token->type == w_here_doc)
	if (token->type == w_append)
	if (token->type == w_pipe)
	if (token->type == w_word)
}

void	make_cmd(t_list *token_list)
{
	t_list	*cmd_list;
	t_cmd	*cur_cmd;
	t_token	*token;

	cur_cmd = NULL;
	while (token_list != NULL)
	{
		token = token_list->content;
		token_to_cmd(token, cur_cmd);
		token_list = token_list->next;
	}
	set_global_command(cmd_list);
}
