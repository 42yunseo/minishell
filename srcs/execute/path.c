/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:58:42 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/30 16:58:43 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"

char	*find_cmd_path(const char *cmd)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	char	*tmp;

	paths = ft_split(ft_getenv("PATH"), ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i++], cmd_path);
		if (access(tmp, X_OK) != -1)
		{
			free(cmd_path);
			free_argv(paths);
			return (tmp);
		}
		free(tmp);
	}
	free(cmd_path);
	free_argv(paths);
	return (NULL);
}

char	*get_cmd_path(const char *cmd)
{
	char	*cmd_path;

	if (ft_strchr(cmd, '/') != NULL && access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') != NULL)
		cmd_path = ft_strdup(cmd);
	else
		cmd_path = find_cmd_path(cmd);
	return (cmd_path);
}
