#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd;

    fd = open("src/", O_RDONLY);
    if (fd == -1)
    {
        perror("src/");
        return 1;
    }
    else
    {
        close(fd);
        printf("File opened successfully\n");
    }
    return 0;
}
