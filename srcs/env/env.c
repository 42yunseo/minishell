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
	t_list		*envp;
	t_envp_node	*node;

	if (name == NULL || *name == '\0')
		return (NULL);
	envp = *get_envp();
	while (envp != NULL)
	{
		node = envp->content;
		if (ft_strcmp(node->key, name) == 0)
			return (node->value);
		envp = envp->next;
	}
	return (NULL);
}

t_list	*get_name_pos(const char *name)
{
	t_list		*pos;
	t_list		*envp;
	t_envp_node	*node;

	envp = *get_envp();
	pos = envp;
	while (pos)
	{
		node = (t_envp_node *) pos->content;
		if (ft_strcmp(node->key, name) == 0)
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
	t_list		*head;
	t_list		*tail;
	t_envp_node	*node;

	if (name == NULL || *name == '\0')
		return (-1);
	head = *get_envp();
	node = head->content;
	while (head->next && node && ft_strcmp(node->key, name) != 0)
	{
		tail = head;
		head = head->next;
		node = head->content;
	}
	if (head == NULL)
		return (-1);
	tail->next = head->next;
	free_envp_node(node);
	free(head);
	return (0);
}
