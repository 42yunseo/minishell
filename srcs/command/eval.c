/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:53:35 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 21:53:35 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "env.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	parse_command(const char *line, int last_exit_status)
{
	t_list	*token_list;
	int		result;

	token_list = tokenize_line(line);
	expand_token(token_list, last_exit_status);
	result = check_token_list(token_list);
	if (result == 0)
		make_ast(token_list);
	ft_lstclear(&token_list, token_free);
	free(token_list);
	return (result);
}

int	read_command(int last_exit_status)
{
	int		result;
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		shell_exit(last_exit_status);
	}
	add_history(line);
	result = parse_command(line, last_exit_status);
	free(line);
	return (result);
}

int	reader_loop(void)
{
	int		last_exit_status;
	t_ast	*cur_command;

	last_exit_status = 0;
	while (1)
	{
		//printf("last_exit_status : %d\n", last_exit_status);
		last_exit_status = read_command(last_exit_status);
		if (last_exit_status == 0)
		{
			cur_command = *get_global_command();
			last_exit_status = execute_command(cur_command);
			dispose_command();
			cur_command = NULL;
		}
		//printf("last_exit_status : %d\n", last_exit_status);
	}
	return (last_exit_status);
}
