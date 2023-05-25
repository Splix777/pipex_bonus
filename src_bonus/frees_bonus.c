/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:51:14 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:51:16 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
		free(pipex->cmd_args[i++]);
	free(pipex->cmd_args);
	free(pipex->cmd);
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths == NULL)
		return ;
	while (pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
}
