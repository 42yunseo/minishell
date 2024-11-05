/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:36:07 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 20:36:08 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_getenv(const char *name)
{
	size_t	len;
	char	**envp;

	if (name == NULL || *name == '\0')
		return (NULL);
	envp = *get_envp();
	len = ft_strlen(name);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, name, len) == 0 && (*envp)[len] == '=')
			return ((*envp) + (len + 1));
		envp++;
	}
	return (NULL);
}

int	get_name_pos(const char *name)
{
	size_t	len;
	int		pos;
	char	**envp;

	len = ft_strlen(name);
	envp = *get_envp();
	pos = 0;
	while (envp[pos] != NULL)
	{
		if (ft_strncmp(*envp, name, len) == 0 && (*envp)[len] == '=')
			break ;
		else
			pos++;
	}
	return (pos);
}

int	ft_setenv(const char *name, const char *value)
{
	char	**envp;
	int		pos;
	char	*tmp1;
	char	*tmp2;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	if (value == NULL)
		return (-1);
	envp = *get_envp();
	pos = get_name_pos(name);
	free(envp[pos]);
	tmp1 = ft_strjoin(name, "=");
	tmp2 = ft_strjoin(tmp1, value);
	free(tmp1);
	envp[pos] = tmp2;
	return (0);
}

int	ft_unsetenv(const char *name)
{
	int		i;
	int		len;
	int		pos;
	char	**ep;
	char	**new_envp;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	i = 0;
	len = get_envp_len();
	pos = get_name_pos(name);
	ep = *get_envp();
	new_envp = (char **)malloc(sizeof(char *) * len);
	while (i < len)
	{
		if (i == pos)
			continue ;
		new_envp[i] = ft_strdup(ep[i]);
		i++;
	}
	new_envp[len] = NULL;
	set_envp(new_envp);
	return (0);
}

/*
envp status
a=a
b=b
c=c
d=d
NULL

이 상황에서 unset(b) 가 호출된다면?

*ep = "b=b" 일때까지 ep 증가
-> 포인터 복사해두고 뒤에서부터 덮어씌우기



*/
