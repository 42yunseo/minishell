/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:10:00 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:10:01 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

int	builtin_export(t_list *list)
{
	if (list == NULL)
		return (builtin_env(NULL));
	// while (list != NULL)
	// {

	// 	list = list->next;
	// }
	return (EXECUTION_SUCCESS);
}
