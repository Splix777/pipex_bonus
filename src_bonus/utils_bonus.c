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
		pipex->cmd_iter++;
		pipex->input_fd = open("/tmp/.pipextemp", O_RDONLY | O_CREAT | O_TRUNC, 0644);
		perror(pipex->argv[1]);
	}
	dup2(pipex->input_fd, STDIN_FILENO);
	close(pipex->input_fd);
}

void	open_outfile(t_pipex *pipex)
{
	pipex->output_fd = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_fd < 0)
	{
		perror(pipex->argv[pipex->argc - 1]);
		exit(126);
	}
	dup2(pipex->output_fd, STDOUT_FILENO);
	close(pipex->output_fd);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (pipex->pid1 == 0)
		execute_cmd(pipex);
	else
		exit_status(pipex);
	close (pipex->pipe[WRITE]);
}

void	exit_status(t_pipex *pipex)
{
	waitpid(pipex->pid1, &pipex->exit_status, 0);
	if (WIFEXITED(pipex->exit_status))
	{
		if (WEXITSTATUS(pipex->exit_status))
			pipex->exit_status = WEXITSTATUS(pipex->exit_status);
	}
	else
		pipex->exit_status = 0;
}

