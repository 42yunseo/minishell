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
		redir->type = r_heredoc;
	if (type == w_append)
	{
		redir->type = r_append;
		redir->oflag = O_WRONLY | O_CREAT | O_APPEND;
	}
}

t_redirect	*make_redirection(t_list *token_list)
{
	enum e_word_type	type;
	t_redirect			*redir;
	t_token				*token;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (redir == NULL)
		return (NULL);
	ft_memset(redir, 0, sizeof(t_redirect));
	token = token_list->content;
	type = token->type;
	token_list = token_list->next;
	token = token_list->content;
	redir->filename = ft_strdup(token->word);
	set_redirection_type_flag(type, redir);
	if (redir->type == r_heredoc)
		heredoc_input(redir);
	return (redir);
}

int	do_redirect(t_redirect *redirect)
{
	int	result;

	result = 0;
	redirect->fd = open(redirect->filename, redirect->oflag, 0644);
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
	while (redirect_list != NULL)
	{
		cur_redirect = redirect_list->content;
		if (cur_redirect->type == r_heredoc)
			result = do_heredoc(cur_redirect);
		else
			result = do_redirect(cur_redirect);
		if (result != 0)
			break ;
		redirect_list = redirect_list->next;
	}
	return (result);
}

void	free_redirection(void *redirection)
{
	t_redirect	*ptr;

	ptr = redirection;
	if (ptr == NULL)
		return ;
	free(ptr->filename);
	free(ptr);
}
