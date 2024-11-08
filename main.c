/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:56:14 by yunseo            #+#    #+#             */
/*   Updated: 2024/08/15 03:56:40 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "command.h"
#include "libft.h"
#include "my_signal.h"
#include <stddef.h>
#include <termios.h>

void	shell_exit(int exit_status)
{
	free_envp();
	ft_putendl_fd("exit", 2);
	exit(exit_status);
}

void	use_args(int argc, char **argv)
{
	argc = (int)argc;
	argv = (void *)argv;
}

void	init_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	if (!isatty(STDIN_FILENO) || !isatty(STDERR_FILENO))
		return (1);
	exit_status = 0;
	use_args(argc, argv);
	init_term();
	set_signals(SIG_SHELL, SIG_SHELL);
	init_envp(envp);
	exit_status = reader_loop();
	shell_exit(exit_status);
}
