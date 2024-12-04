/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:10:28 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:10:28 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

int	builtin_unset(t_list *list)
{
	int	result;

	result = 0;
	if (list == NULL)
		return (result);
	while (list != NULL)
	{
		ft_unsetenv(list->content);
		list = list->next;
	}
	return (result);
}
