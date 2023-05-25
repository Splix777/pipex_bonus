/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:30:18 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/19 12:30:19 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->input_fd = open(argv[1], O_RDONLY);
	if (pipex->input_fd < 0)
		msg_error(argv[1]);
	close(pipex->pipe[READ]);
	dup2(pipex->pipe[WRITE], STDOUT_FILENO);
	dup2(pipex->input_fd, STDIN_FILENO);
	close(pipex->input_fd);
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd = get_cmd(pipex, pipex->cmd_paths, pipex->cmd_args[0]);
	if (pipex->cmd == NULL)
		exit_errors(pipex, argv[2], 1, 127);
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
		msg_error(argv[2]);
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_fd < 0)
		msg_error(argv[4]);
	close(pipex->pipe[WRITE]);
	dup2(pipex->pipe[READ], STDIN_FILENO);
	dup2(pipex->output_fd, STDOUT_FILENO);
	close(pipex->output_fd);
	pipex->cmd_args = ft_split(argv[3], ' ');
	pipex->cmd = get_cmd(pipex, pipex->cmd_paths, pipex->cmd_args[0]);
	if (pipex->cmd == NULL)
		exit_errors(pipex, argv[3], 1, 127);
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
		msg_error(argv[3]);
}
