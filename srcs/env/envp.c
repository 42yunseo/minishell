/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:12:55 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 20:12:56 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

char	***get_envp(void)
{
	static char	**envp;

	return (&envp);
}

void	set_envp(char **new_envp)
{
	free_envp();
	*get_envp() = new_envp;
}

void	free_envp(void)
{
	char	**envp;
	int		i;

	envp = *get_envp();
	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
	envp = NULL;
}

int	get_envp_len(void)
{
	int		len;
	char	**envp;

	len = 0;
	envp = *get_envp();
	while (envp[len] != NULL)
		len++;
	return (len);
}

void	init_envp(char **envp)
{
	char	***envpp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	envpp = get_envp();
	while (envp[len] != NULL)
		len++;
	*envpp = (char **)malloc(sizeof(char *) * (len + 1));
	if (*envpp == NULL)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		(*envpp)[i] = ft_strdup(envp[i]);
		i++;
	}
	(*envpp)[len] = NULL;
}
