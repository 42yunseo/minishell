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
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"

#include <stdio.h>

/*

bash-5.2$ echo "$HOME"
/Users/yungyoseo
bash-5.2$ echo '$HOME'
$HOME
bash-5.2$ echo "'$HOME"
'/Users/yungyoseo
bash-5.2$ echo '"$HOME"'
"$HOME"

*/

int	parse_command(const char *line)
{
	//int 		result;
	//int			need_here_doc;
	t_list	*token_list;
	t_token	*cur_token;
	//t_word_list	*list;

	//need_here_doc = 0;
	token_list = token_line(line);
	while (token_list != NULL)
	{
		cur_token = token_list->content;
		if (cur_token->type == w_word)
			expand_word(cur_token);
		printf("tok : %s\n", cur_token->word);
		token_list = token_list->next;
	}
	//return (result);
	return (0);
}

int	read_command(void)
{
	int		result;
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL || *line == '\0')
		return (1);
	add_history(line);
	result = parse_command(line);
	free(line);
	return (result);
}

int	reader_loop(void)
{
	int		last_exit_status;
	t_cmd	*cur_command;

	last_exit_status = 0;
	while (1)
	{
		if (read_command() == 0)
		{
			cur_command = *get_global_command();
			//last_exit_status = execute_command(cur_command);
			dispose_command(cur_command);
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
