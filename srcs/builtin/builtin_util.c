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
	size_t	len;

	cmd = args->content;
	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_list *args)
{
	int		(*fp)(t_list *);
	int		result;
	char	*cmd;
	size_t	len;

	fp = NULL;
	result = 0;
	cmd = args->content;
	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0)
		fp = builtin_echo;
	else if (ft_strncmp(cmd, "cd", len) == 0)
		fp = builtin_cd;
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		fp = builtin_pwd;
	else if (ft_strncmp(cmd, "export", len) == 0)
		fp = builtin_export;
	else if (ft_strncmp(cmd, "unset", len) == 0)
		fp = builtin_unset;
	else if (ft_strncmp(cmd, "env", len) == 0)
		fp = builtin_env;
	else if (ft_strncmp(cmd, "exit", len) == 0)
		fp = builtin_exit;
	result = fp(args->next);
	return (result);
}
