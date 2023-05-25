/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:50:52 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:53 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_here_doc(char *str)
{
	if (strcmp(str, "here_doc") == 0)
		return (1);
	return (0);
}

void	do_here_doc(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->here_doc = 1;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->limiter = ft_strjoin(argv[2], "\n");
	pipex->cmd_iter = 3;
	pipex->cmd_count = argc - 3;
	pipex->input_fd = 0;
	here_doc(pipex);
	dup2(pipex->input_fd, STDIN_FILENO);
	free(pipex->limiter);
}

void	here_doc(t_pipex *pipex)
{
	if (pipe(pipex->pipe) < 0)
		ft_putendl_fd("Error: Pipe failed", 2);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (pipex->pid1 == 0)
		write_to_pipe(pipex);
	else
	{
		waitpid(pipex->pid1, NULL, 0);
		close(pipex->pipe[WRITE]);
		dup2(pipex->pipe[READ], STDIN_FILENO);
		close(pipex->pipe[READ]);
	}
}

void	write_to_pipe(t_pipex *pipex)
{
	char	*line;

	close(pipex->pipe[READ]);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(line, pipex->limiter) == 0)
			break ;
		ft_putstr_fd(line, pipex->pipe[WRITE]);
		free(line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(pipex->pipe[WRITE]);
	exit(0);
}
