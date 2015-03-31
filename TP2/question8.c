#include    <stdlib.h>
#include    <stdio.h>
#include    <signal.h>
#include    <time.h>

void *T2()
{
    int duration=333;
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
    int duration=1000;
    unsigned int i=0;
    printf("T3\n");
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}void *T4()
{
    int duration=2000;
    unsigned int i=0;
    printf("T4\n");
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}

int main(int ac, char **av) {

    while (1) {
        printf("BOUCLE!\n"); 
        T2();
        T3();
        T4();
        T2();
        T3();
        T2();
        T4();
        T2();
        T3();
        T2();
        T4();
        T3();
        T2();
        
    }

}
