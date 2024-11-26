/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 02:18:54 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/26 02:18:56 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	print_err(char *word)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd("'", 2);
}

int	check_pipe(t_list *token_list)
{
	t_token	*cur_token;
	t_token	*next_token;

	cur_token = token_list->content;
	token_list = token_list->next;
	if (token_list == NULL)
	{
		print_err(cur_token->word);
		return (2);
	}
	next_token = token_list->content;
	if (next_token->type == w_pipe)
	{
		print_err(next_token->word);
		return (2);
	}
	return (0);
}

int	check_redirection(t_list *token_list)
{
	t_token	*next_token;

	token_list = token_list->next;
	if (token_list == NULL)
	{
		print_err("newline");
		return (2);
	}
	next_token = token_list->content;
	if (next_token->type != w_word)
	{
		print_err(next_token->word);
		return (2);
	}
	return (0);
}

int	check_token_list(t_list *token_list)
{
	t_list	*ptr;
	t_token	*token;
	int		result;

	result = 0;
	ptr = token_list;
	while (ptr != NULL && result == 0)
	{
		token = ptr->content;
		if (token->type == w_word)
			result = 0;
		else if (token->type == w_pipe)
			result = check_pipe(ptr);
		else
			result = check_redirection(ptr);
		ptr = ptr->next;
	}
	return (result);
}
