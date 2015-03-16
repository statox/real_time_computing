#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

void listen_signal();
void sighandler(int);

int main (int argc, const char* argv[])
{
	listen_signal();

	pause();	

	return EXIT_SUCCESS;
}

void listen_signal()
{
	signal(SIGUSR1, sighandler);
}

void sighandler(int signum)
{
	pid_t pid = getpid();
	
	sleep(1);
	printf("Le processus courant '%d' a recu un signal '%d'\n", pid, signum);
}

