/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:36:07 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 20:36:08 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_getenv(const char *name)
{
	size_t		len;
	t_list		*envp;
	t_envp_node	*node;

	if (name == NULL || *name == '\0')
		return (NULL);
	envp = *get_envp();
	len = ft_strlen(name);
	while (envp != NULL)
	{
		node = envp->content;
		if (ft_strncmp(node->key, name, len) == 0)
			return (node->value);
		envp = envp->next;
	}
	return (NULL);
}

t_list	*get_name_pos(const char *name)
{
	size_t		len;
	t_list		*pos;
	t_list		*envp;
	t_envp_node	*node;

	len = ft_strlen(name);
	envp = *get_envp();
	pos = envp;
	while (pos)
	{
		node = (t_envp_node *) pos->content;
		if (ft_strncmp(node->key, name, len) == 0)
			return (pos);
		pos = pos->next;
	}
	return (NULL);
}

int	ft_setenv(const char *name, const char *value)
{
	t_list		*envp;
	t_list		*pos;
	t_envp_node	*node;

	if (name == NULL || *name == '\0')
		return (-1);
	if (value == NULL)
		return (-1);
	envp = *get_envp();
	pos = get_name_pos(name);
	if (pos != NULL)
	{
		node = pos->content;
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
		ft_lstadd_back(&envp, ft_lstnew(make_envp_node(name, value)));
	return (0);
}

int	ft_unsetenv(const char *name)
{
	t_list		*fast;
	t_list		*slow;
	t_envp_node	*node;
	int			len;

	if (name == NULL || *name == '\0')
		return (-1);
	len = ft_strlen(name);
	slow = *get_envp();
	node = slow->content;
	while (slow->next && node && ft_strncmp(node->key, name, len) != 0)
	{
		fast = slow;
		slow = slow->next;
		node = slow->content;
	}
	if (slow == NULL)
		return (-1);
	fast->next = slow->next;
	free_envp_node(node);
	free(slow);
	return (0);
}
