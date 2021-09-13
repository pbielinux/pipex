#include "../headers/pipex.h"

void    error(char *err_message)
{
    perror(ft_strjoin("\033[31mError: ", err_message));
    exit(EXIT_FAILURE);
}

int main()
{
    int     fd[2];
    int     nbytes;
    pid_t   child_pid;
    char    str[] = "fill the pipe!\n";
    char    buffer[100];

    pipe(fd);

    if((child_pid = fork()) == -1)
        error("Fork failed");
    
    // The child process
    if(child_pid == 0)
    {
        close(fd[p_read]); // Child proccess does not need this end
        write(fd[p_write], str, ft_strlen(str)+1);
        exit(0);
    }
    // Parent Process
    else
    {
        close(fd[p_write]); // Parent proccess does not need this end

        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("\033[1;94mRead %d bytes from string:\033[1;32m %s", nbytes, buffer);
    }
    return (0);
}