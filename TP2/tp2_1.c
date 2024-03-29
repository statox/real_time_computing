#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* function which pause the program with a millisecond precision */
void *do_work(int duration);

int main (int argc, const char* argv[])
{
    printf ("my pid: %d\n", getpid());

    do_work(6000);
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
