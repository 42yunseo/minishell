/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:09:53 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:09:54 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

void	print_env_list(void *list)
{
	t_list		*env_list;
	t_envp_node	*node;

	env_list = list;
	node = env_list->content;
	ft_putstr_fd(node->key, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(node->value, STDOUT_FILENO);
}

int	builtin_env(t_list *list)
{
	t_list	*envp_list;

	list = (void *)list;
	envp_list = *get_envp();
	ft_lstiter(envp_list, print_env_list);
	return (EXECUTE_SUCCESS);
}