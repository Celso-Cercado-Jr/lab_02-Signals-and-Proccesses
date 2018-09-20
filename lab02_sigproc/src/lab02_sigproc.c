/*
 ** sigint.c -- grabs SIGINT
 *
 * Source:  http://beej.us/guide/bgipc/html/single/bgipc.html#signals
 *          http://beej.us/guide/bgipc/examples/sigint.c
 *
 * Modified by: hurdleg@algonquincollege.com
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
	//printf("PID %d = Child Received USR1\n", getpid());
    got_usr1 = usr1Happened; // set usr1 to value of one
}

int main(void)
{
	int numChildren;// number of children
    struct sigaction sa; // sig action declaration

    got_usr1 = 0; //initialize the got_usr1

    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;

    printf("Enter the number of children: ");
    scanf("%d", &numChildren);

    numChildren = got_usr1; // set the number of children to usr1 process.

    if ((numChildren = fork()) < 0) {
            perror("fork");
            exit(1);
        }
    if((numChildren = fork()) == 0){


    printf("PID %d = Parent Running...\n", getppid());
    printf("PID %d = Child Received USR1\n", getpid());
    printf("PID %d = Child Exiting..\n", getpid());
    printf("PID %d = Child Finished, parent exiting.\n", getppid());

    sleep(-1);
    }


    return 0;
}

