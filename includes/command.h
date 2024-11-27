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

enum e_redirect_type
{
	r_input,
	r_output,
	r_append,
	r_heredoc
};

typedef struct s_redirect
{
	enum e_redirect_type	type;
	char					*filename;
	int						fd;
	int						oflag;
}	t_redirect;

typedef struct s_cmd
{
	t_list			*args;
	t_list			*redirects;
}	t_cmd;

typedef struct s_pipe
{
	struct s_ast_node	*l_node;
	struct s_ast_node	*r_node;
}	t_pipe;

enum e_node_type
{
	node_cmd,
	node_pipe
};

typedef struct s_ast_node
{
	enum e_node_type	type;
	union
	{
		t_pipe	*pipe;
		t_cmd	*cmd;
	}	u_value;
}	t_ast_node;

typedef struct s_ast
{
	t_ast_node	*root;
	int			last_exit_status;
}	t_ast;

//command.c
t_ast		**get_global_command(void);
void		set_global_command(t_ast *new_command);
t_cmd		*ft_cmd_new(void);

// token.c
t_list		*tokenize_line(const char *line);
void		token_free(void *ptr);

// eval.c
int			parse_command(const char *line, int last_exit_status);
int			read_command(int last_exit_status);
int			reader_loop(void);

// expansion.c
void		expand_token(t_list *token_list, int last_exit_status);

// type.c
int			is_isf(char c);
int			is_redirect(char c);
int			is_quote(char c);

// ast.c
void		make_ast(t_list *token_list);
t_ast_node	*ft_new_ast_node(void *value, enum e_node_type type);

// execute.c
int			execute_command(t_ast *cur_command);
int			execute_node(t_ast_node *node);
int			execute_cmd(t_cmd *cmd);

// simple.c
int			execute_simple(t_list *args);

// pipe.c
int			execute_pipe(t_pipe *pipe_node);

// redirect.c
int			execute_redirect(t_list *redirect_list);
t_redirect	*make_redirection(t_list *token_list);
void		free_redirection(void *redirect);

// heredoc.c
int			do_heredoc(char *delimiter);

// path.c
void		free_argv(char **args);

// syntax.c
int			check_token_list(t_list *token_list);

// dispose.c
void		dispose_command(void);

// pasre.c
t_ast_node	*parse_node(t_list *token_list);
t_ast_node	*parse_cmd(t_list *token_list);
t_ast_node	*parse_pipe(t_ast_node *l_node, t_list *token_list);

t_cmd		*make_cmd(t_list *token_list);

//t_pipe		*make_pipe();

void		add_str(char **src, char *part);

#endif

/*
파이프에 대한 dup2 처리 이후
다이렉션에 대한 dup2 처리.

ls -l | wc -l < a
같은 경우 입력을 ls -l 의 결과로 받지 않고, a로 입력을 받음. (파이프 출력이 무시됨.)

ls -l > a | wc -l
위의 경우도 마찬가지. ls -l의 결과가 wc로 넘어가지 않고, a로 출력됨.

*/
