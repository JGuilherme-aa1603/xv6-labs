#include "kernel/types.h"
#include "user/user.h"

int
main() {
    int pipe1[2], pipe2[2];
    char buf;

    pipe(pipe1);
    pipe(pipe2);

    int pid = fork();

    if (pid == 0) {
        read(pipe1[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(pipe2[1], &buf, 1);
    } else {
        write(pipe1[1], "x", 1);
        read(pipe2[0], &buf, 1);
        printf("%d: received pong\n", getpid());
    }

    exit(0);
}