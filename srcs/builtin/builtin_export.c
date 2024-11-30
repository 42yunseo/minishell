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

void	print_export_err(char *str)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	export_name_check(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_')
			i++;
		else
			return (-1);
	}
	return (i);
}

void	env_setting(char *str, int idx)
{
	char	*name;
	char	*value;

	name = ft_substr(str, 0, idx);
	value = ft_strdup(&str[idx + 1]);
	ft_setenv(name, value);
	free(name);
	free(value);
}

void	print_export(void *content)
{
	t_envp_node	*node;

	node = content;
	if (node == NULL)
		return ;
	if (ft_strcmp(node->key, "_") == 0)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->key, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(node->value, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}

int	builtin_export(t_list *list)
{
	char	*str;
	int		idx;

	if (list == NULL)
		ft_lstiter(*get_envp(), print_export);
	while (list != NULL)
	{
		str = list->content;
		idx = export_name_check(str);
		if (ft_strchr(str, '=') == NULL && idx >= 0)
		{
			list = list->next;
			continue ;
		}
		if (idx <= 0)
		{
			print_export_err(str);
			return (EXECUTE_FAILURE);
		}
		env_setting(str, idx);
		list = list->next;
	}
	return (EXECUTE_SUCCESS);
}
