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

enum e_token_type
{
	w_input_redirect,
	w_output_redirect,
	w_here_doc,
	w_append,
	w_pipe,
	w_word
};

typedef struct s_token
{
	char				*word;
	enum e_token_type	type;
}	t_token;

// typedef struct s_word_list
// {
// 	char				*word;
// 	struct s_word_list	*next;
// }	t_word_list;

typedef struct s_cmd
{
	char			*cmd;
	t_list			*args;
	int				pipe[2];
	struct s_cmd	*next_cmd;
}	t_cmd;

// command.c
t_cmd	**get_global_command(void);
void	set_global_command(t_cmd *new_command);
void	dispose_command(t_cmd *command);

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
