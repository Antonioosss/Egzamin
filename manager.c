#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include "manager.h"

void create_workers(int n, int pipes[][2], pid_t pids[], char *names[]) {
    for (int i = 0; i < n; ++i) {
        pipe(pipes[i]);
        if ((pids[i] = fork()) == 0) {
            close(pipes[i][1]);
            dup2(pipes[i][0], STDIN_FILENO);
            char buffer[100];
            printf("%s: Gotowy do pracy\n", names[i]);
            signal(SIGHUP,  SIG_IGN); // zdefiniujesz dalej w worker.c
            signal(SIGUSR1, SIG_IGN);
            signal(SIGINT,  SIG_IGN);
            while (fgets(buffer, sizeof(buffer), stdin)) {
                if (strncmp(buffer, "Podaj imię", 10) == 0) {
                    printf("My name is %s\n", names[i]);
                } else if (strncmp(buffer, "PID?", 4) == 0) {
                    printf("%s: My PID is %d\n", names[i], getpid());
                }
            }
            exit(0);
        } else {
            close(pipes[i][0]);
        }
    }
}
