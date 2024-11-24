/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:53:09 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/08 22:53:10 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>
#include <stdio.h>

void	set_redirection_type_flag(enum e_word_type type, t_redirect *redir)
{
	if (type == w_input_redirect)
	{
		redir->type = r_input;
		redir->oflag = O_RDONLY;
	}
	if (type == w_output_redirect)
	{
		redir->type = r_output;
		redir->oflag = O_WRONLY | O_CREAT | O_TRUNC;
	}
	if (type == w_here_doc)
	{
		redir->type = r_heredoc;
	}
	if (type == w_append)
	{
		redir->type = r_append;
		redir->oflag = O_WRONLY | O_CREAT | O_APPEND;
	}
}

t_redirect	*make_redirection(enum e_word_type type, t_token *token)
{
	t_redirect	*redir;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (redir == NULL)
		return (NULL);
	redir->fd = 0;
	redir->filename = token->word;
	set_redirection_type_flag(type, redir);
	return (redir);
}

int	do_redirect(t_redirect *redirect)
{
	int	result;

	result = 0;
	redirect->fd = open(redirect->filename, redirect->oflag);
	if (redirect->fd == -1)
	{
		result = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(redirect->filename);
	}
	else
	{
		if (redirect->type == r_input)
			dup2(redirect->fd, STDIN_FILENO);
		else
			dup2(redirect->fd, STDOUT_FILENO);
		close(redirect->fd);
	}
	return (result);
}

int	execute_redirect(t_list *redirect_list)
{
	t_redirect	*cur_redirect;
	int			result;

	result = 0;
	printf("redirect_list : %p\n", redirect_list);
	while (redirect_list != NULL)
	{
		cur_redirect = redirect_list->content;
		if (cur_redirect->type == r_heredoc)
			continue ;
		else
			result = do_redirect(cur_redirect);
		if (result != 0)
			break ;
		redirect_list = redirect_list->next;
	}
	return (result);
}

void	free_redirection(t_redirect *redirection)
{
	free(redirection->filename);
	free(redirection);
}
