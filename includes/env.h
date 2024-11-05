/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:13:21 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 20:13:22 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// envp.c
char	***get_envp(void);
void	set_envp(char **new_envp);
void	free_envp(char **envp);
int		get_envp_len(void);
void	init_envp(char **envp);

// env.c
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value);
int		ft_unsetenv(const char *name);

#endif