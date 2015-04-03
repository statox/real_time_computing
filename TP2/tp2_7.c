#include    <stdlib.h>
#include    <stdio.h>
#include    <signal.h>
#include    <time.h>


timer_t gTimerid;

void *do_work(int duration)
{

    unsigned int i=0;
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}

void start_timer(void)
{
    struct itimerspec value;

    /* les deux variables doivent avoir la meme valeur pour 
     * permettre au timer de se réarmer à chaque fois
     */
    value.it_value.tv_sec = 1;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 1;
    value.it_interval.tv_nsec = 0;

    timer_create (CLOCK_REALTIME, NULL, &gTimerid);
    timer_settime (gTimerid, 0, &value, NULL);
}

void timer_callback(int sig) {
    printf("Nouveau signal envoye par le timer\n", sig);
    do_work(500);
}

int main(int ac, char **av)
{
    (void) signal(SIGALRM, timer_callback);
    start_timer();
    while(1);

}
