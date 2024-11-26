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

void	set_envp(t_list	*new_envp)
{
	free_envp();
	*get_envp() = new_envp;
}

void	free_envp(void)
{
	t_list		*envp;
	t_list		*tmp;
	t_envp_node	*node;

	envp = *get_envp();
	while (envp != NULL)
	{
		node = (t_envp_node *)envp->content;
		free(node->key);
		free(node->value);
		free(envp->content);
		tmp = envp->next;
		free(envp);
		envp = tmp;
	}
}

void	sset_envp(t_envp_node *node, char *env)
{
	int		idx;

	idx = get_equal_idx(env);
	node->key = ft_substr(env, 0, idx);
	node->value = ft_substr(&env[idx + 1], 0, ft_strlen(&env[idx + 1]));
}

int	get_equal_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '=')
			return idx;
		idx++;
	}
	return -1;
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
	t_list	*head;
	char	*name;
	char	*value;
	int		idx;

	head = *get_envp();
	while (*envp != NULL)
	{
		idx = get_equal_idx(*envp);
		name = ft_substr(*envp, 0, idx);
		value = ft_substr(&(*envp[idx + 1]), 0, ft_strlen(&(*envp[idx + 1])));
		ft_lstadd_back(&head, ft_lstnew(make_envp_node(name, value)));
		envp++;
	}
	set_envp(head);
}


/*
char	***get_envp(void)
{
	static char	**envp;

	return (&envp);
}

void	set_envp(char **new_envp)
{
	free_envp();
	*get_envp() = new_envp;
}

void	free_envp(void)
{
	char	**envp;
	int		i;

	envp = *get_envp();
	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
	envp = NULL;
}

int	get_envp_len(void)
{
	int		len;
	char	**envp;

	len = 0;
	envp = *get_envp();
	while (envp[len] != NULL)
		len++;
	return (len);
}

void	init_envp(char **envp)
{
	char	***envpp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	envpp = get_envp();
	while (envp[len] != NULL)
		len++;
	*envpp = (char **)malloc(sizeof(char *) * (len + 1));
	if (*envpp == NULL)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		(*envpp)[i] = ft_strdup(envp[i]);
		i++;
	}
	(*envpp)[len] = NULL;
}
*/