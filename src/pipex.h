/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:30:39 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/19 12:30:40 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		input_fd;
	int		output_fd;
	char	*paths;
	char	*cmd;
	char	**cmd_paths;
	char	**cmd_args;
}			t_pipex;

// childs.c
char		*get_cmd(t_pipex *pipex, char **paths, char *cmd);
void		first_child(t_pipex *pipex, char **argv, char **envp);
void		second_child(t_pipex *pipex, char **argv, char **envp);
// errors.c
void		msg_error(char *msg);
void		exit_errors(t_pipex *pipex, char *msg, int reason, int code);
// frees.c
void		free_child(t_pipex *pipex);
void		free_parent(t_pipex *pipex);
// utils.c
char		*get_env_path(char **envp);
void		free_pipes(t_pipex *pipex);
void		wait_childs(pid_t pid1, pid_t pid2);

#endif
