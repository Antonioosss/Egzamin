#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "worker.h"

static const char *worker_name;

void handle_sighup(int sig) {
    printf("%s: Odpoczywam\n", worker_name);
}

void handle_sigusr1(int sig) {
    printf("%s: Startuję!\n", worker_name);
}

void handle_sigint(int sig) {
    printf("%s: Kończę\n", worker_name);
    exit(0);
}

void setup_signal_handlers(const char *name) {
    worker_name = name;
    signal(SIGHUP,  handle_sighup);
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGINT,  handle_sigint);
}
