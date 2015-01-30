#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/* defining macro functions for P() and V() */
#define P(value) sem_wait(value)
#define V(value) sem_post(value)

void *print_message_function_1();
void *print_message_function_2();

/* declaring the semaphore used to sync the threads */
sem_t sem1;
sem_t sem2;

int main (int argc, const char* argv[])
{
    pthread_t thread1, thread2;
    int  iret1, iret2;

    /* intialize the semaphore with a value of 1 */
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    /* Create independent threads each of which will execute function */
    iret1 = pthread_create( &thread1, NULL, print_message_function_1, NULL);
    if(iret1)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create( &thread2, NULL, print_message_function_2, NULL);
    if(iret2)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }

    printf("pthread_create() for thread 1 returns: %d\n",iret1);
    printf("pthread_create() for thread 2 returns: %d\n",iret2);

    /* Wait till threads are complete before main continues. */
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL ); 

    exit(EXIT_SUCCESS);
}

/* This function is executed and free the semaphore */
void *print_message_function_1()
{
    printf("systeme ");

    V(&sem1);
    P(&sem2);

    printf("- ");

    V(&sem1);
}

/* This function needs the semaphore to be free so it is executed after the 
 * previous one.
 */
void *print_message_function_2()
{
    P(&sem1);

    printf("temps ");

    V(&sem2);
    P(&sem1);

    printf("reel ");
}

