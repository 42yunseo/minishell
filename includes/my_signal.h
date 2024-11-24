/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:39:43 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/05 21:39:44 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H
# include <signal.h>

# define SIG_DEFAULT	0
# define SIG_IGNORE		1
# define SIG_SHELL		2
# define SIG_CHILD		3

void	set_signals(int sig_int, int sig_quit);
void	init_signal(void);
void	sig_child(int signo);

#endif
