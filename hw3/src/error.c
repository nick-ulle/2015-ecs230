
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(EXIT_FAILURE);
}

