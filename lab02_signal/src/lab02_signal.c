/*
 ** sigint.c -- grabs SIGINT
 *
 * Source:  http://beej.us/guide/bgipc/html/single/bgipc.html#signals
 *          http://beej.us/guide/bgipc/examples/sigint.c
 *
 * Modified by: hurdleg@algonquincollege.com1
 *
 * Usage:
 *  From Momentics IDE, run program; notice PID; enter some text, but don't hit the enter key
 *  At Neutrino prompt, issue the command: kill -s SIGINT <PID>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t got_usr1;


int usr1Happened = 1;

void sigusr1_handler(int sig)
{
    got_usr1 = usr1Happened; // set usr1 to value of one

}

int main(void)
{
    struct sigaction sa;

    got_usr1 = 0; //initialize the got

    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;

    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("PID %d: Running...\n", getpid());
    while (!got_usr1) {
        printf("PID %d: Received USR1\n", getpid());
       // sigusr1_handler(got_usr1);
        sleep(1);
    }
    printf("PID %d: Exiting!\n", getpid());
    printf("Stopped!\n");

    return 0;
}

