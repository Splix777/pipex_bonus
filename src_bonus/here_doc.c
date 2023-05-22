#include "pipex_bonus.h"

void    here_doc(t_pipex *pipex, char *limiter, int argc, char **argv)
{
    char    *line;
    
    if (argc < 6)
        msg_error("Error: Wrong number of Arguments");
    if (pipe(pipex->pipe) == -1)
        msg_error("pipe");
    pipex->pid1 = fork();
    if (pipex->pid1 == 0)
    {
        close(pipex->pipe[READ]);
        while (get_next_line(&line))
        {
            if (ft_strncmp(line, limiter, ft_strlen(limiter)))
                exit(0);
            write(pipex->pipe[WRITE], line, ft_strlen(line));
        }
    }
    else
    {
        close(pipex->pipe[WRITE]);
        dup2(pipex->pipe[0], STDIN_FILENO);
    }
}