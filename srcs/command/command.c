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

t_list	**get_global_command(void)
{
	static t_list	*g_command;

	return (&g_command);
}

void	set_global_command(t_list *new_command)
{
	t_list	**g_command;

	g_command = get_global_command();
	// command free;
	*g_command = new_command;
}

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	ft_memset(cmd, 0, sizeof(t_cmd));
	return (cmd);
}
