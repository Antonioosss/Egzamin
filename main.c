#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "manager.h"
#include "worker.h"

#define NUM_WORKERS 4

int main() {
    char *names[NUM_WORKERS] = {"Alice", "Bob", "Eve", "Tom"};
    int pipes[NUM_WORKERS][2];
    pid_t pids[NUM_WORKERS];

    create_workers(NUM_WORKERS, pipes, pids, names);

    sleep(1); // Czekaj aż dzieci się przygotują

    // Wyślij im komendę przez pipe
    for (int i = 0; i < NUM_WORKERS; ++i) {
        write(pipes[i][1], "Podaj imię\n", 11);
        write(pipes[i][1], "PID?\n", 5);
    }

    sleep(1); // Czekaj aż wypiszą

    // Wyślij sygnały
    for (int i = 0; i < NUM_WORKERS; ++i)
        kill(pids[i], SIGHUP);
    sleep(1);
    for (int i = 0; i < NUM_WORKERS; ++i)
        kill(pids[i], SIGUSR1);
    sleep(1);
    for (int i = 0; i < NUM_WORKERS; ++i)
        kill(pids[i], SIGINT);

    for (int i = 0; i < NUM_WORKERS; ++i)
        waitpid(pids[i], NULL, 0);

    return 0;
}
