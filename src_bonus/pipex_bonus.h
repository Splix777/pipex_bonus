/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:51:01 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:51:02 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*open, close, read, write, access, dup, dup2, execve, exit, fork, pipe,
	unlink*/
# include <fcntl.h>
# include <unistd.h>

/*malloc, free*/
# include <stdlib.h>

/*perror, strerror*/
# include <stdio.h>
# include <string.h>

/*wait, waitpid*/
# include <sys/types.h>
# include <sys/wait.h>

/*My Own Libraries*/
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"

# define READ 0
# define WRITE 1
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

typedef struct s_pipex
{
	pid_t	pid1;
	int		pipe[2];
	int		input_fd;
	int		output_fd;
	int		cmd_iter;
	int		cmd_count;
	int		here_doc;
	int		argc;
	char	*limiter;
	char	*paths;
	char	*cmd;
	char	**argv;
	char	**envp;
	char	**cmd_paths;
	char	**cmd_args;
}			t_pipex;

// childs_bonus.c
char		*get_cmd(t_pipex *pipex, char **paths, char *cmd);
void		send_through_pipe(t_pipex *pipex);
void		execute_cmd(t_pipex *pipex);
// do_pipex_bonus.c
void		do_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
// errors_bonus.c
void		msg_error(char *msg);
void		exit_errors(t_pipex *pipex, char *msg, int reason, int code);
// free_bonus.c
void		free_cmd(t_pipex *pipex);
void		free_paths(t_pipex *pipex);
// here_doc_bonus.c
int			is_here_doc(char *str);
void		do_here_doc(t_pipex *pipex, int argc, char **argv, char **envp);
void		here_doc(t_pipex *pipex);
void		write_to_pipe(t_pipex *pipex);
// utils_bonus.c
char		*get_env_path(char **envp);
void		open_infile(t_pipex *pipex);
void		open_outfile(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
void		close_fd(t_pipex *pipex);

#endif
