#include "../headers/pipex.h"

void    error(char *err_message)
{
    perror(ft_strjoin("\033[31mError: ", err_message));
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int     fd[2];
    int     nbytes;
    pid_t   child_pid;
    char    buffer[100];

    pipe(fd);

    (void)argc;

    if((child_pid = fork()) == -1)
        error("Fork failed");
    
    // The child process
    if(child_pid == 0)
    {
        close(fd[p_read]); // Child proccess does not need this end
        write(fd[p_write], argv[1], ft_strlen(argv[1])+1);
        exit(0);
    }
    // Parent Process
    else
    {
        close(fd[p_write]); // Parent proccess does not need this end

        nbytes = read(fd[p_read], buffer, sizeof(buffer));
        printf("Read %d bytes from Input\n\nOutput\033[1;32m: %sforgeeks.org\n", nbytes, buffer);
    }
    return (0);
}