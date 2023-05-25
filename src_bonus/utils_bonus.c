/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:51:32 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:51:33 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_env_path(char **envp)
{
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == NULL)
		return (NULL);
	return (*envp + 5);
}

void	open_infile(t_pipex *pipex)
{
	pipex->input_fd = open(pipex->argv[1], O_RDONLY);
	if (pipex->input_fd < 0)
	{
		perror(pipex->argv[1]);
		pipex->cmd_iter++;
	}
	dup2(pipex->input_fd, STDIN_FILENO);
}

void	open_outfile(t_pipex *pipex)
{
	pipex->output_fd = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_fd < 0)
	{
		perror(pipex->argv[pipex->argc - 1]);
		close_pipes(pipex);
		close_fd(pipex);
		exit(126);
	}
	dup2(pipex->output_fd, STDOUT_FILENO);
	close(pipex->output_fd);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
}

void	close_fd(t_pipex *pipex)
{
	close(pipex->input_fd);
	close(pipex->output_fd);
}
