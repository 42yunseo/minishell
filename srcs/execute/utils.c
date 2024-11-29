/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:46:35 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/26 18:46:36 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "command.h"

char	**list_to_argv(t_list *list)
{
	char	**argv;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(list);
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		argv[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	argv[len] = NULL;
	return (argv);
}

char	*env_to_char(t_envp_node *node)
{
	char	*target;

	target = NULL;
	add_str(&target, ft_strdup(node->key));
	add_str(&target, ft_strdup("="));
	add_str(&target, ft_strdup(node->value));
	return (target);
}

char	**list_to_envp(t_list *envp_list)
{
	char	**envp;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(envp_list);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		envp[i] = env_to_char((t_envp_node *)envp_list->content);
		i++;
		envp_list = envp_list->next;
	}
	envp[len] = NULL;
	return (envp);
}
