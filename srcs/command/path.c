/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:15:48 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/22 16:15:49 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

#include <stdio.h>


void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}
