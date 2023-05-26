/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:51:23 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:51:24 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_putendl_fd("Error: Wrong number of arguments", 2);
	if (argc >= 6 && is_here_doc(argv[1]))
		do_here_doc(&pipex, argc, argv, envp);
	else
		do_pipex(&pipex, argc, argv, envp);
	while (pipex.cmd_iter < pipex.cmd_count)
	{
		send_through_pipe(&pipex);
		pipex.cmd_iter++;
	}
	open_outfile(&pipex);
	close_pipes(&pipex);
	//close_fd(&pipex);
	return (0);
}
