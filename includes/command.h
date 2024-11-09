/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:04:14 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:04:14 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"

enum e_word_type
{
	w_input_redirect,
	w_output_redirect,
	w_append,
	w_here_doc,
	w_pipe,
	w_word
};

typedef struct s_token
{
	char				*word;
	enum e_word_type	type;
}	t_token;

typedef struct s_redirect
{
	enum e_word_type	type;
	int					fd;
	char				*filename;
}	t_redirect;

typedef struct s_cmd
{
	t_list			*args;
	int				pflag;
	int				pipe[2];
	t_list			*redirects;
	int				here_doc_flag;
	char			*here_doc_str;
	int				origin_stdin;
	int				origin_stdout;
	int				origin_stderr;
	struct s_cmd	*next_cmd;
}	t_cmd;

// command.c
t_list	**get_global_command(void);
void	set_global_command(t_list *new_command);
t_cmd	*ft_cmd_new(void);

// token.c
t_list	*token_line(const char *line);
void	ft_token_free(void *ptr);

int		parse_command(const char *line);
int		read_command(void);
int		reader_loop(void);

// expansion.c
void	expand_token(t_list *token_list);

// type.c
int		is_isf(char c);
int		is_redirect(char c);
int		is_quote(char c);

#endif

/*
파이프에 대한 dup2 처리 이후
다이렉션에 대한 dup2 처리.

ls -l | wc -l < a
같은 경우 입력을 ls -l 의 결과로 받지 않고, a로 입력을 받음. (파이프 출력이 무시됨.)

ls -l > a | wc -l
위의 경우도 마찬가지. ls -l의 결과가 wc로 넘어가지 않고, a로 출력됨.

*/
