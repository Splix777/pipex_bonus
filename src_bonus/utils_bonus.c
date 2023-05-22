/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:30:59 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/19 12:31:00 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_env_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

void	free_pipes(t_pipex *pipex)
{
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
}

void	wait_childs(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;
	int	exit_status1;
	int	exit_status2;

	exit_status1 = 0;
	exit_status2 = 0;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status1))
	{
		if (WEXITSTATUS(status1))
			exit_status1 = WEXITSTATUS(status1);
	}
	if (WIFEXITED(status2))
	{
		if (WEXITSTATUS(status2))
			exit_status2 = WEXITSTATUS(status2);
	}
	if (exit_status1 != 0)
		exit(0);
	if (exit_status2 != 0)
		exit(0);
	exit(0);
}

/*It calls waitpid twice to wait for the termination of both child
processes (pid1 and pid2).

The exit status of each child process is stored in status1 and
status2, respectively.

The function then checks if each child process terminated normally
using the WIFEXITED macro. This macro evaluates to true if the
child process terminated normally (not due to a signal).

If the child process exited with a non-zero status (indicating an error),
it retrieves the exit status using WEXITSTATUS and stores it in
exit_status1 or exit_status2, depending on the child process.

Finally, it prints the exit status of each child process using ft_printf.*/