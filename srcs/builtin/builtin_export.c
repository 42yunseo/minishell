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
	char	*str;
	char	*name;
	char	*value;
	int		idx;

	if (list == NULL)
		return (builtin_env(NULL));
	while (list != NULL)
	{
		str = list->content;
		idx = get_equal_idx(str);
		if (idx != -1)
		{
			name = ft_substr(str, 0, idx);
			value = ft_strdup(&str[idx + 1]);
			ft_setenv(name, value);
			free(name);
			free(value);
		}
		list = list->next;
	}
	return (EXECUTE_SUCCESS);
}
