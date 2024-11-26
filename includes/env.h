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
# include "libft.h"

typedef struct s_envp_node
{
	char				*key;
	char				*value;
}	t_envp_node;

// envp.c
t_list		**get_envp(void);
t_envp_node	*make_envp_node(const char *name, const char *value);
void		free_envp(void);
int			get_equal_idx(char *str);


// env.c
char	*ft_getenv(const char *name);
int	ft_setenv(const char *name, const char *value);
int	ft_unsetenv(const char *name);


#endif