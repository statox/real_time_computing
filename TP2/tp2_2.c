#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

/* function which pause the program with a millisecond precision */
void *do_work(int duration);

/* Handles a signal by printing its number when the signal arrives */
void signalHandler(int signum){
    printf ("\nHey! You got a signal %d\n", signum);
}

int main (int argc, const char* argv[])
{
    printf ("my pid: %d\n", getpid());
    /* handler of SIGUSR1 signal */
    signal (SIGUSR1, signalHandler);

    do_work(60000);

}


void *do_work(int duration)
{

    unsigned int i=0;
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}
