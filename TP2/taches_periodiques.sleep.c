#define _POSIX_C_SOURCE 200809L

#include    <stdlib.h>
#include    <stdio.h>
#include    <inttypes.h>
#include    <math.h>
#include    <time.h>
#include    <unistd.h>
#include    <signal.h>

/* Question 6 version avec alarm */
void *do_work(int duration);

int main (int argc, const char* argv[]) {
    int cpt = 0;

    while (cpt<20) {
        cpt++;
        printf("iteration %d\n", cpt); 
        usleep(500);
        do_work(500);
    }
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
