/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:50:38 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:40 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_cmd(t_pipex *pipex, char **paths, char *cm)
{
	char	*tmp;
	char	*final_cmd;

	if (cm[0] == '/' || !ft_strncmp("../", cm, 3) || !ft_strncmp("./", cm, 2))
		return (cm);
	if (pipex->cmd_paths == NULL)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		final_cmd = ft_strjoin(tmp, cm);
		free(tmp);
		if (access(final_cmd, F_OK | X_OK) == 0)
			return (final_cmd);
		free(final_cmd);
		paths++;
	}
	return (NULL);
}

void	send_through_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe) < 0)
		perror("Error: ");
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		perror("Error: ");
	if (pipex->pid1 == 0)
	{
		close(pipex->pipe[READ]);
		dup2(pipex->pipe[WRITE], STDOUT_FILENO);
		execute_cmd(pipex);
	}
	else
	{
		close(pipex->pipe[WRITE]);
		dup2(pipex->pipe[READ], STDIN_FILENO);
		waitpid(pipex->pid1, NULL, 0);
	}
}

void	execute_cmd(t_pipex *pipex)
{
	pipex->paths = get_env_path(pipex->envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	pipex->cmd_args = ft_split(pipex->argv[pipex->cmd_iter], ' ');
	pipex->cmd = get_cmd(pipex, pipex->cmd_paths, pipex->cmd_args[0]);
	free_paths(pipex);
	if (pipex->cmd == NULL)
		exit_errors(pipex, pipex->argv[pipex->cmd_iter], 1, 127);
	if (execve(pipex->cmd, pipex->cmd_args, pipex->envp) == -1)
		msg_error(pipex->cmd);
}
