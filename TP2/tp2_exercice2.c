#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sighandler(int);
void do_work(unsigned int);

unsigned int cpt;

int main (int argc, const char* argv[])
{
	cpt = 0;
	unsigned int cpt1 = 0;

	pid_t pid = getpid();
	
	printf("AVANT SIGNAL :  cpt = %d / cpt1 = %d\n", cpt, cpt1);

	signal(SIGUSR1, sighandler);

	printf("APRES SIGNAL :  cpt = %d / cpt1 = %d\n", cpt, cpt1);

	while(1)
	{
		if ( cpt - cpt1 != 0 )
		{
			do_work(2000);

			printf("Le signal USR1 (id: %d) a ete traite\n\n", cpt1);
			
			cpt1++;
		}
	}	

	return EXIT_SUCCESS;
}

void sighandler(int signum)
{
	cpt++;
	pid_t pid = getpid();
	
	printf("Le processus courant '%d' a recu un signal '%d' (id: %d)\n", pid, signum, cpt);
}

void do_work(unsigned int duration)
{
        unsigned int i;
        int coef = 280000;

        for ( i = 0 ; i < coef * duration ; i++ )
        {
                asm volatile ("nop");
        }
}

