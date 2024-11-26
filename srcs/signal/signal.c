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
#include "libft.h"
#include <stdio.h>
#include "readline/readline.h"
#include <unistd.h>
#include <stdlib.h>

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_child(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", 2);
	if (signo == SIGQUIT)
		ft_putendl_fd("Quit: 3", 2);
}

void	set_signals(int sig_int, int sig_quit)
{
	if (sig_int == SIG_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SIG_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == SIG_SHELL)
		signal(SIGINT, sigint_handler);
	if (sig_int == SIG_CHILD)
		signal(SIGINT, sig_child);
	if (sig_quit == SIG_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SIG_IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == SIG_CHILD)
		signal(SIGQUIT, sig_child);
}

void	init_signal(void)
{
	set_signals(SIG_SHELL, SIG_IGNORE);
	signal(SIGTERM, SIG_IGN);
}
