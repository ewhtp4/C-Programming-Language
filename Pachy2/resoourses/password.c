#define  _POSIX_C_SOURCE  200809L
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
//#include "pachy.h"

int main(void)
{
    FILE  *cmd= ((void*)0);;
    int status;

    cmd = popen("/usr/bin/sudo -S id -un 2>/dev/null", "w");
    if (!cmd) {
        fprintf(stderr, "Cannot run sudo: %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    fprintf(cmd, "Password\n");
    fflush(cmd);

    status = pclose(cmd);
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == EXIT_SUCCESS)
            fprintf(stderr, "No errors.\n");
        else
            fprintf(stderr, "Command failed with exit status %d.\n", WEXITSTATUS(status));
    } else
    if (WIFSIGNALED(status))
        fprintf(stderr, "Command killed by signal %d.\n", WTERMSIG(status));
    else
        fprintf(stderr, "Command failed.\n");

    return EXIT_SUCCESS;
}