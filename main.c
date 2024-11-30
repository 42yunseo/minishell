/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:56:14 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/30 19:46:44 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "command.h"
#include "libft.h"
#include "my_signal.h"
#include <stddef.h>

void	shell_exit(int exit_status)
{
	ft_lstclear(get_envp(), free_envp_node);
	set_signals(SIG_DEFAULT, SIG_DEFAULT);
	signal(SIGTERM, SIG_DFL);
	dispose_command();
	exit(exit_status);
}

void	use_args(int argc, char **argv)
{
	argc = (int)argc;
	argv = (void *)argv;
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

//	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || 
//	!isatty(STDERR_FILENO))
//		return (1);
	exit_status = 0;
	use_args(argc, argv);
	init_signal();
	init_envp(envp);
	exit_status = reader_loop();
	shell_exit(exit_status);
}
