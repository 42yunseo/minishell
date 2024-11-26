/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 02:13:25 by yunseo            #+#    #+#             */
/*   Updated: 2024/11/26 02:13:26 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "my_signal.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>

void	heredoc_child(char *delimiter, int pipe_fd[2])
{
	char	*line;
	size_t	len;

	set_signals(SIG_DEFAULT, SIG_IGNORE);
	close(pipe_fd[0]);
	len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(delimiter, line, len) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	heredoc_parent(pid_t pid)
{
	int	status;
	int	result;
	int	signo;

	status = 0;
	set_signals(SIG_CHILD, SIG_IGNORE);
	result = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		result = (128 + signo);
	}
	else if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	set_signals(SIG_SHELL, SIG_IGNORE);
	return (result);
}

int	do_heredoc(char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		result;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	result = 0;
	if (pid == 0)
		heredoc_child(delimiter, pipe_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	result = heredoc_parent(pid);
	close(pipe_fd[0]);
	return (result);
}
