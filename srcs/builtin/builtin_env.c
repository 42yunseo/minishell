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

int	builtin_env(t_list *list)
{
	char	**envp;

	list = (void *)list;
	envp = *get_envp();
	while (*envp != NULL)
	{
		ft_putendl_fd(*envp, STDOUT_FILENO);
		envp++;
	}
	return (EXECUTION_SUCCESS);
}
