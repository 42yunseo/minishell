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

void	print_unset_err(char *str)
{
	ft_putstr_fd("bash: unset: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	name_check(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(*name))
	{
		print_unset_err(name);
		return (1);
	}
	else if (ft_strchr(name, '=') != NULL)
	{
		print_unset_err(name);
		return (1);
	}
	while (name[i] != '\0' && (ft_isalnum(name[i]) || name[i] == '_'))
		i++;
	if (name[i] != '\0')
	{
		print_unset_err(name);
		return (1);
	}
	return (0);
}

int	builtin_unset(t_list *list)
{
	int	result;

	result = 0;
	if (list == NULL)
		return (result);
	while (list != NULL)
	{
		if (name_check(list->content) != 0)
			result = 1;
		ft_unsetenv(list->content);
		list = list->next;
	}
	return (result);
}
