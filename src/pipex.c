/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:30:54 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/19 12:30:55 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_putendl_fd("Error: Wrong number of arguments", 2), 1);
	if (pipe(pipex.pipe) == -1)
		return (ft_putendl_fd("Error: Pipe failed", 2), 1);
	pipex.paths = get_env_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(&pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(&pipex, argv, envp);
	free_pipes(&pipex);
	free_parent(&pipex);
	wait_childs(pipex.pid1, pipex.pid2);
	return (0);
}

/*Exit status 0: This typically indicates successful termination of a process.
It means that the process completed its execution without encountering any
errors.

Exit status 1: This is often used as a generic error code. It indicates that
the process encountered an unspecified error or exception during its execution.

Exit status 2: It is commonly used to indicate misuse or improper usage of a
process or command. It may suggest that the command-line arguments or
options provided were incorrect or violated the expected usage.

Exit status 127: This code often indicates that the command or executable
being invoked was not found. It suggests that the system could not locate
the specified command or that it is not in the system's executable search path.

Exit status 126: This code typically indicates that the invoked command or
executable was found but cannot be executed due to insufficient permissions.
It suggests that the user or process does not have the necessary permissions
to run the command.

Exit status 128+: Exit codes in the range of 128 and above are often used to
represent specific signals or exceptions that caused the termination of the 
process. For example, an exit status of 139 (128 + 11) might indicate a
segmentation fault or an invalid memory access.
*/
