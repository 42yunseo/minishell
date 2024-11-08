/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:39:36 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/05 21:39:37 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_signal.h"
#include "readline/readline.h"
#include <unistd.h>

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		write(1, "\a", 1);
	}
}

void	set_signals(int sig_int, int sig_quit)
{
	if (sig_int == SIG_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SIG_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == SIG_SHELL)
		signal(SIGINT, signal_handler);
	if (sig_quit == SIG_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SIG_IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == SIG_SHELL)
		signal(SIGQUIT, signal_handler);
}
