/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:02:17 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/25 17:02:18 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"

enum e_word_type	get_token_type(char *word)
{
	enum e_word_type	type;

	if (word[0] == '<')
	{
		if (word[1] == '<')
			type = w_here_doc;
		else
			type = w_input_redirect;
	}
	else if (word[0] == '>')
	{
		if (word[1] == '>')
			type = w_append;
		else
			type = w_output_redirect;
	}
	else if (word[0] == '|')
		type = w_pipe;
	else
		type = w_word;
	return (type);
}

t_token	*ft_token_new(char *word)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->word = word;
	token->type = get_token_type(word);
	return (token);
}

size_t	get_token_len(const char *line)
{
	size_t	len;
	char	symbol;

	len = 0;
	if (line[len] == '|')
		len++;
	else if (ft_strchr("<>", line[len]) != NULL)
	{
		symbol = line[len++];
		if (line[len] == symbol)
			len++;
	}
	else
	{
		while (line[len] != '\0' && !ft_strchr(" \t\n<>|", line[len]))
		{
			if (is_quote(line[len]))
			{
				symbol = line[len++];
				while (line[len] != '\0' && line[len] != symbol)
					len++;
			}
			len++;
		}
	}
	return (len);
}

t_list	*token_line(const char *line)
{
	t_token	*token;
	t_list	*token_list;
	size_t	len;

	token_list = NULL;
	len = 0;
	while (*line != '\0')
	{
		if (*line == ' ' || *line == '\t' || *line == '\n')
			line++;
		else
		{
			len = get_token_len(line);
			token = ft_token_new(ft_substr(line, 0, len));
			ft_lstadd_back(&token_list, ft_lstnew(token));
			line += len;
		}
	}
	return (token_list);
}

void	ft_token_free(void *ptr)
{
	t_token	*token;

	token = ptr;
	free(token->word);
	free(token);
}

/*

토큰화 규칙

1. 초기 토큰화는 공백문자를 기준으로 한다. (' ', '\t', '\n')
2. 인용부호 ('\"', '\'')는 인용부호를 한 묶음으로 취급한다.

*/

// $HOME <- 얘를 한 토큰으로.
// $ HOME
