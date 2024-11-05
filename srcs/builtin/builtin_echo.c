/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:44 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:06:45 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(t_list *list)
{
	int		display_return;

	display_return = 1;
	while (list != NULL)
	{
		if (ft_strncmp(list->content, "-n", 2) == 0)
			display_return = 0;
		else
			break ;
		list = list->next;
	}
	while (list != NULL)
	{
		ft_putstr_fd(list->content, STDOUT_FILENO);
		list = list->next;
		if (list != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (display_return == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXECUTION_SUCCESS);
}
