#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/* defining the number of waker threads  */
#define N 10

/* defining macro functions for P() and V() */
#define P(value) sem_wait(value)
#define V(value) sem_post(value)

/* defining macro functions for mutexes lock and unlock */
#define lock(value)     pthread_mutex_lock(value)
#define unlock(value)   pthread_mutex_unlock(value)

void *waker_function();
void *waiter_function();

/* declaring the semaphore used to wake up the waiter */
sem_t sem1;
/* mutex protecting the output of the wakers */
pthread_mutex_t mut;

int main (int argc, const char* argv[])
{
    pthread_t waiter;
    pthread_t wakers[N];
    int i = 0;

    /* intialize the semaphore with a value of the number of wakers threads */
    sem_init(&sem1, 0, 0);

    /*Create independent threads each of which will execute function*/
    pthread_create(&waiter, NULL, waiter_function, NULL );

    for (i=0; i<N; ++i)
    {
        pthread_create(&wakers[i], NULL, waker_function, NULL );
    }

    /* Wait till threads are complete before main continues. */
    pthread_join( waiter, NULL );
    for (i=0; i<N; ++i)
    {
        pthread_join( wakers[N], NULL );
    }

    exit(EXIT_SUCCESS);
}


void *waker_function()
{
    lock(&mut);
    int value;
    sem_getvalue(&sem1, &value);
    printf ("new waker thread sem=%d\n", value);
    V(&sem1);

    unlock(&mut);
}

void *waiter_function()
{
    int i = 0;

    while (i<N)
    {
        printf ("i: %d\n", i);
        if (P(&sem1) == 0)
            ++i;
    }

    printf ("I m the waiter and I m waked up\n");
}

