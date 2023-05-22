/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:30:24 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/19 12:30:25 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
		free(pipex->cmd_args[i++]);
	free(pipex->cmd_args);
	free(pipex->cmd);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
}
