/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:57:02 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 18:57:02 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include <stdio.h>

char	*get_dirname(t_list *list)
{
	char	*dirname;

	dirname = NULL;
	if (list == NULL)
	{
		dirname = ft_getenv("HOME");
		if (dirname == NULL)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	}
	else if (list->next != NULL)
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	else
		dirname = list->content;
	return (dirname);
}

int	builtin_cd(t_list *list)
{
	char	*dirname;
	char	*cwd;

	dirname = get_dirname(list);
	if (dirname == NULL)
		return (EXECUTE_FAILURE);
	if (chdir(dirname) == 0)
	{
		cwd = getcwd(NULL, 0);
		ft_setenv("PWD", cwd);
		free(cwd);
		return (EXECUTE_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(dirname);
		return (EXECUTE_FAILURE);
	}
}
