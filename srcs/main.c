#include "../headers/pipex.h"

int main(int argc, char **argv)
{
    int     fd;
    int     bytes_read;
    char    buffer[BUFFER_SIZE];

    fd = STDIN_FILENO;
    if (argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);

    return (0);
}