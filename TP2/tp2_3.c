#include    <inttypes.h>
#include    <math.h>
#include    <time.h>
#include    <stdio.h>
#include    <unistd.h>
#include    <signal.h>

#define _POSIX_C_SOURCE 200809L

void  ALARMhandler(int sig)
{
    signal(SIGALRM, SIG_IGN);           /* ignore this signal */
    printf("Hello");
    signal(SIGALRM, ALARMhandler);      /* reinstall the handler */

}

void *do_work(int duration)
{


    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds

    printf("Current time: %"PRIdMAX".%03ld seconds since the Epoch\n", (intmax_t)s, ms);


    unsigned int i=0;
    printf("do work\n");
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}


int main(int argc, char *argv[])
{
    while (1)
    {
       sleep(1);
       do_work(500);
    }
}
