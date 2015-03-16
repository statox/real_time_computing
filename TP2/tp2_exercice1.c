#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void do_work(unsigned int);

int main (int argc, const char* argv[])
{
	do_work(atoi(argv[1])); // Execute do_work pour argv[0] millisecondes

	return EXIT_SUCCESS;
}

/* Execute une pause pendant duration millisecondes  */
void do_work(unsigned int duration)
{
	unsigned int i;
	int coef = 280000;

	for ( i = 0 ; i < coef * duration ; i++ )
	{
		asm volatile ("nop");
	}
}
