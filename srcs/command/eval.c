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
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"


int	parse_command(const char *line)
{
	// int 		result;
	//int			need_here_doc;
	t_list	*token_list;
	//t_word_list	*list;

	//need_here_doc = 0;
	token_list = token_line(line);
	expand_token(token_list);
	//make_cmd(token_list);
	ft_lstclear(&token_list, NULL);
//	ft_lstclear(&token_list, ft_token_free);
	free(token_list);
	return (0);
}

int	read_command(void)
{
	int		result;
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
		return (1);
	add_history(line);
	result = parse_command(line);
	free(line);
	return (result);
}

int	reader_loop(void)
{
	int		last_exit_status;
	t_list	*cmd_list;
	//t_cmd	*cur_command;

	last_exit_status = 0;
	while (1)
	{
		if (read_command() == 0)
		{
			cmd_list = *get_global_command();
			//last_exit_status = execute_command(cur_command);
			free(cmd_list);
		}
		else
		{
			last_exit_status = 0;
			break ;
		}
	}
	return (last_exit_status);
}

/* Execute a simple command that is hopefully defined in a disk file
   somewhere.

   1) fork ()
   2) connect pipes
   3) look up the command
   4) do redirections
   5) execve ()
   6) If the execve failed, see if the file has executable mode set.
   If so, and it isn't a directory, then execute its contents as
   a shell script.

   Note that the filename hashing stuff has to take place up here,
   in the parent.  This is probably why the Bourne style shells
   don't handle it, since that would require them to go through
   this gnarly hair, for no good reason.

   NOTE: callers expect this to fork or exit(). */

/* Name of a shell function to call when a command name is not found. */
