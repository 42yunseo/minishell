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
		shell_exit(last_exit_status);
	add_history(line);
	result = parse_command(line, last_exit_status);
	free(line);
	return (result);
}


/*
print ast will remove
*/
void	print_node(t_ast_node *node);


void	print_pipe(t_pipe *pipe_node)
{
	printf("pipe ptr : %p\n", pipe_node);
	if (pipe_node == NULL)
		return ;
	printf("l node : \n");
	print_node(pipe_node->l_node);
	printf("\nr node : \n");
	print_node(pipe_node->r_node);
}

void	print_cmd(t_cmd *cmd)
{
	printf("cmd ptr ; %p\n", cmd);
	if (cmd == NULL)
		return ;
	printf("cmd's args \n");
	int i = 0;
	while (cmd->args != NULL)
	{
		printf("arg[%d] : %s\n", i++, (char *)cmd->args->content);
		cmd->args = cmd->args->next;
	}
	printf("\n");
}

void	print_node(t_ast_node *node)
{
	printf("node ptr : %p\n", node);
	if (node == NULL)
		return ;
	printf("node type : %s\n", node->type == node_cmd ? "CMD" : "PIPE");
	if (node->type == node_cmd)
		print_cmd(node->u_value.cmd);
	if (node->type == node_pipe)
		print_pipe(node->u_value.pipe);
	printf("\n");
}

void	print_ast(t_ast *ast)
{
	printf("ast ptr : %p\n", ast);
	if (ast == NULL)
		return ;
	print_node(ast->root);
}

/*
remove end
*/

int	reader_loop(void)
{
	int		last_exit_status;
	t_ast	*cur_command;

	last_exit_status = 0;
	while (1)
	{
		last_exit_status = read_command(last_exit_status);
		if (last_exit_status == 0)
		{
			cur_command = *get_global_command();
			//print_ast(cur_command);
			last_exit_status = execute_command(cur_command);
			dispose_command();
			cur_command = NULL;
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
