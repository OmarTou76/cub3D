#include "../include/cub3D.h"

int main(int argc, char const *argv[])
{
    if (argc != 2 || !is_valid_ext(argv[1]))
    {
        printf("Error\n[USAGE]: %s <FILENAME>.cub .\n", argv[0]);
        return (1);
    }
    printf("Hello from cub\n");
    return 0;
}
