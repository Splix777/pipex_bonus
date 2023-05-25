/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:50:46 by fsalazar          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:47 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*The perror function prints the error message to the standard
error stream (stderr), followed by a colon and a space, and
then the corresponding error message string based on the value
of errno. It looks up the error message associated with the
current value of errno and prints it.*/
void	msg_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	exit_errors(t_pipex *pipex, char *msg, int reason, int code)
{
	write(2, msg, ft_strlen(msg));
	if (reason == 1)
		write(2, ": command not found\n", 20);
	free_cmd(pipex);
	exit(code);
}
