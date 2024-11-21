/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:10:48 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:10:48 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(t_list *list)
{
	list = (void *)list;
	ft_putendl_fd("exit", STDERR_FILENO);
	return (EXECUTE_SUCCESS);
}
