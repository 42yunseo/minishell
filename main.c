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
#include <stddef.h>

void	shell_exit(int exit_status)
{
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

	exit_status = 0;
	use_args(argc, argv);
	set_signals();
	init_envp(envp);
	exit_status = reader_loop();
	//shell_exit(exit_status);
	return (exit_status);
}
