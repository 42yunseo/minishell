/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:57:29 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 18:57:30 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"
# include "libft.h"

# define EXECUTE_SUCCESS	0
# define EXECUTE_FAILURE	1

int		builtin_echo(t_list *list);
int		builtin_cd(t_list *list);
int		builtin_pwd(t_list *list);
int		builtin_export(t_list *list);
int		builtin_unset(t_list *list);
int		builtin_env(t_list *list);
int		builtin_exit(t_list *list);

// util function
int		isabuiltin(t_list *args);
int		execute_builtin(t_list *args);

#endif
