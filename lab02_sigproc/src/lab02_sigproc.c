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

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t got_usr1;

int usr1Happened = 1;

void sigusr1_handler(int sig)
{
	printf("PID %d = Child Received USR1\n", getpid());

    got_usr1 = usr1Happened; // set usr1 to value of one
}

int foo(const char *whoami)
{
	printf("I am a %s.  My pid is:%d  my ppid is %d\n",
			whoami, getpid(), getppid() );
	return 1;
}


int main(void)
{
	int numChildren;// number of children

    int status=0;// status wait

    printf("Enter the number of children: ");
    scanf("%d", &numChildren);

    numChildren = fork(); // fork the numChildren
    foo("parent"); // call parent

    if (numChildren < 0) {
            perror("fork");
            exit(1);
        }

	   if(numChildren == 0){ // Children Process
		   sigusr1_handler(numChildren);// call the SIGUSR1
		   printf("PID %d = Child Exiting..\n", getpid());
		   printf("PID %d = Children finished, parent exiting.\n", getppid());
		   sleep(-1);

	   }
	   wait(&status);  /* only the parent waits */

    return 0;
}

