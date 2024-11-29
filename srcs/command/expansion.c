/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:19:16 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/31 16:19:17 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "command.h"

#include <stdio.h>

void	add_str(char **src, char *part)
{
	char	*result;

	if (*src == NULL)
		*src = ft_strdup("");
	if (part == NULL)
		part = ft_strdup("");
	result = ft_strjoin(*src, part);
	free(*src);
	free(part);
	*src = result;
}

int	dollar_expand(char *word, char **result, int last_exit_status)
{
	size_t	len;
	char	*env;
	char	*tmp;

	len = 0;
	word++;
	if (*word == '?')
	{
		add_str(result, ft_itoa(last_exit_status));
		return (2);
	}
	while (word[len] != '\0' && !ft_strchr(" \t\n\'\"$", word[len]))
		len++;
	if (len == 0)
	{
		add_str(result, ft_strdup("$"));
		return (1);
	}
	tmp = ft_substr(word, 0, len);
	if (ft_getenv(tmp) == NULL)
		env = NULL;
	else
		env = ft_strdup(ft_getenv(tmp));
	add_str(result, env);
	free(tmp);
	return (len + 1);
}

int	quote_expand(char *word, char **result, int last_exit_status)
{
	char	quote;
	size_t	len;

	quote = *word;
	len = 1;
	if (word[len] == quote)
	{
		add_str(result, NULL);
		return (2);
	}
	while (word[len] != '\0' && word[len] != quote)
	{
		if (word[len] == '$' && quote == '\"')
			len += dollar_expand(&word[len], result, last_exit_status);
		else
		{
			add_str(result, ft_substr(word, len, 1));
			len++;
		}
	}
	if (word[len] == quote)
		len++;
	return (len);
}

void	expand_word(t_token *token, int last_exit_status)
{
	size_t	len;
	char	*result;

	len = 0;
	result = NULL;
	while (token->word[len] != '\0')
	{
		if (token->word[len] == '$')
			len += dollar_expand(&token->word[len], &result, last_exit_status);
		else if (is_quote(token->word[len]))
			len += quote_expand(&token->word[len], &result, last_exit_status);
		else
		{
			add_str(&result, ft_substr(token->word, len, 1));
			len++;
		}
	}
	free(token->word);
	token->word = result;
}

void	expand_token(t_list *token_list, int last_exit_status)
{
	t_list	*ptr;
	t_token	*token;

	ptr = token_list;
	while (ptr != NULL)
	{
		token = ptr->content;
		if (token->type == w_word)
			expand_word(token, last_exit_status);
		ptr = ptr->next;
	}
}
