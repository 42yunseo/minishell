/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:12:55 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 20:12:56 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

t_list	**get_envp(void)
{
	static t_list	*envp;

	return (&envp);
}

void	free_envp_node(void *content)
{
	t_envp_node	*node;

	node = content;
	if (content == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(content);
}

int	get_equal_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}

t_envp_node	*make_envp_node(const char *name, const char *value)
{
	t_envp_node	*node;

	node = (t_envp_node *)malloc(sizeof(t_envp_node));
	if (node == NULL)
		return (NULL);
	node->key = ft_strdup(name);
	node->value = ft_strdup(value);
	return (node);
}

void	init_envp(char **envp)
{
	t_list	**head;
	char	*name;
	char	*value;
	int		idx;

	head = get_envp();
	while (*envp != NULL)
	{
		idx = get_equal_idx(*envp);
		name = ft_substr(*envp, 0, idx);
		value = ft_strdup(*(envp) + idx + 1);
		ft_lstadd_back(head, ft_lstnew(make_envp_node(name, value)));
		free(name);
		free(value);
		envp++;
	}
}
