#include    <unistd.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <signal.h>
#include    <time.h>

timer_t gTimerid;
void *T2()
{
    int duration=166;
    unsigned int i=0;
    printf("T2\n");
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}
void *T3()
{
    int duration=500;
    unsigned int i=0;
    printf("T3\n");
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}void *T4()
{
    int duration=1000;
    unsigned int i=0;
    printf("T4\n");
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
    value.it_value.tv_sec = 2;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 2;
    value.it_interval.tv_nsec = 0;

    timer_create (CLOCK_REALTIME, NULL, &gTimerid);
    timer_settime (gTimerid, 0, &value, NULL);
}
void timer_callback(int sig) {
    /*printf("Nouveau signal envoye par le timer\n", sig);*/
}
int main(int ac, char **av) {

    (void) signal(SIGALRM, timer_callback);
    start_timer();
    while (1) {
        printf("BOUCLE!\n"); 
        T2();
        T3();
        T4();
        pause();
        T2();
        pause();
        T3();
        pause();
        T2();
        T4();
        pause();
        T2();
        T3();
        pause();
        T2();
        T4();
        T3();
        pause();
        T2();
        pause();
    }

}
