#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/* ── Signal Handlers ─────────────────────────────────── */

void handle_sigint(int sig) {
    (void)sig;
    printf("\n[Monitor Service] Monitor Service shutting down safely.\n");
    fflush(stdout);
    exit(0);
}

void handle_sigusr1(int sig) {
    (void)sig;
    printf("\n[Monitor Service] System status requested by administrator.\n");
    fflush(stdout);
}

void handle_sigterm(int sig) {
    (void)sig;
    printf("\n[Monitor Service] Emergency shutdown signal received.\n");
    fflush(stdout);
    exit(1);
}

/* ── Main ────────────────────────────────────────────── */

int main(void) {
    /* Register signal handlers using sigaction (preferred over signal()) */
    struct sigaction sa_int, sa_usr1, sa_term;

    memset(&sa_int,  0, sizeof(sa_int));
    memset(&sa_usr1, 0, sizeof(sa_usr1));
    memset(&sa_term, 0, sizeof(sa_term));

    sa_int.sa_handler  = handle_sigint;
    sa_usr1.sa_handler = handle_sigusr1;
    sa_term.sa_handler = handle_sigterm;

    sigaction(SIGINT,  &sa_int,  NULL);
    sigaction(SIGUSR1, &sa_usr1, NULL);
    sigaction(SIGTERM, &sa_term, NULL);

    printf("[Monitor Service] Started. PID = %d\n", getpid());
    printf("[Monitor Service] Registered handlers: SIGINT | SIGUSR1 | SIGTERM\n");
    fflush(stdout);

    /* Main loop: print status every 5 seconds */
    while (1) {
        printf("[Monitor Service] System running normally...\n");
        fflush(stdout);
        sleep(5);
    }

    return 0;
}
