/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:08:02 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/21 17:08:03 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	isabuiltin(t_list *args)
{
	char	*cmd;

	cmd = args->content;
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_list *args)
{
	int		(*fp)(t_list *);
	int		result;
	char	*cmd;

	fp = NULL;
	result = 0;
	cmd = args->content;
	if (ft_strcmp(cmd, "echo") == 0)
		fp = builtin_echo;
	else if (ft_strcmp(cmd, "cd") == 0)
		fp = builtin_cd;
	else if (ft_strcmp(cmd, "pwd") == 0)
		fp = builtin_pwd;
	else if (ft_strcmp(cmd, "export") == 0)
		fp = builtin_export;
	else if (ft_strcmp(cmd, "unset") == 0)
		fp = builtin_unset;
	else if (ft_strcmp(cmd, "env") == 0)
		fp = builtin_env;
	else if (ft_strcmp(cmd, "exit") == 0)
		fp = builtin_exit;
	result = fp(args->next);
	return (result);
}
