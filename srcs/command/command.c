/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:25:58 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/18 15:26:02 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_cmd	**get_global_command(void)
{
	static t_cmd	*g_command;

	return (&g_command);
}

void	set_global_command(t_cmd *new_command)
{
	t_cmd	**g_command;

	g_command = get_global_command();
	dispose_command(*g_command);
	*g_command = new_command;
}

void	dispose_command(t_cmd *command)
{
	free(command);
}
