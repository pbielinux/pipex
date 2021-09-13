#include "../headers/pipex.h"

int main(int argc, char **argv)
{
    (void)argc;
    char    *bin_file;
    int     redirect_fd;

    bin_file = argv[1];

    if (fork() == 0)
    {   
        // Child process
        if ((redirect_fd = open("redirect_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
        {
            fprintf(stderr, "Error opening file\n");
            exit(1);
        }
        dup2(redirect_fd, STDOUT_FILENO);
        close(redirect_fd);

        if (execvp(bin_file, &argv[1]) == -1)
        {
            fprintf(stderr, "Error executing %s\n", bin_file);
            exit(1);
        }
    }
    else
    {
        wait(NULL);
        printf(BGRN"\ndone!\n");
    }
    return (0);
}