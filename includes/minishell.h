/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:55:41 by yunseo            #+#    #+#             */
/*   Updated: 2024/08/22 16:49:42 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXECUTION_SUCCESS	0
# define EXECUTION_FAILURE	1

void	shell_exit(int exit_status);

/*
RPEL programming

READ
PARSE
EXECUTE
LOOP
*/

/*

builtin function list

◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

*/

/*
	char	*readline(const char *prompt);

	void	rl_clear_history(void);

	int		rl_one_new_line(void);

	void	rl_replace_line(const char *text, int clear_undo);

	void	rl_redisplay(void);

	void	add_history(char *string);

	int		printf(const char * format, ...);

	void	*malloc(size_t size);
	void	free(void *ptr);

	ssize_t	write(int fd, const void *buf, size_t count);
	int		access(const char *pathname, int mode);
	int		open(const char *pathname, int flags);
	ssize_t	read(int fd, void *buf, size_t count);
	int		close(int fd);

	pid_t	fork(void);
	pit_t	wait(int *wstatus);
	pid_t	waitpid(pid_t pid, int *wstatus, int options);
	pid_t	wait3(int *wstatus, int options, struct rusage *rusage);
	pid_t	wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);

	sighandler_t	signal(int signum, sighandler_t handler);
	int				sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	int				sigemptyset(sigset_t *set);
	int				sigaddset(sigset_t *set, int signum);

	int		kill(pid_t pid, int sig);
	void	exit(int status);

	char	*getcwd(char *buf, size_t size);
	int		chdir(const char *path);

	int	stat(const char *pathname, struct stat *statbuf);
	int	lstat(const char *pathname, struct stat *statbuf);
	int	fstat(int fd, struct stat *statbuf);

	int	unlink(const char *pathname);
	int	execve(const char *pathname, char *const argv[], char *const envp[]);
	int	dup(int oldfd);
	int	dup2(int oldfd, int newfd);
	int	pipe(int pipefd[2]);

	DIR				*opendir(const char *name);
	struct dirent	*readdir(DIR *dirp);
	int				closedir(DIR *dirp);

	char	*strerror(int errnum);
	void	perror(const char *s);

	int		isatty(int fd);
	char	*ttyname(int fd);
	int		ttyslot(void);

	int		ioctl(int fd, unsigned long request, ...);
	char	*getenv(const char *name);

	int	tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
	int	tcgetattr(int fd, const struct termios *termios_p);

	int		tgetent(char *bp, const char *name);
	int		tgetflag(char *id);
	int		tgetnum(char *id);
	char	*tgetstr(char *id, char **area);
	char	*tgoto(const char *cap, int col, int row);
	int		tputs(const char *str, int affcnt, int (*putc)(int));
*/

#endif
