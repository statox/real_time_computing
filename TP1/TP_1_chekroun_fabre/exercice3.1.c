#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/* Ce programme teste notre code avec plusieurs écrivains */

/* defining macro functions for P() and V() */
#define P(value) sem_wait(&value)
#define V(value) sem_post(&value)

/* defining macro functions for mutexes lock and unlock */
#define lock(value)     pthread_mutex_lock(&value)
#define unlock(value)   pthread_mutex_unlock(&value)

/* defining the number of cases in the buffer */
#define N   5

/* structure of the buffer */
int buffer[N];

/* reading head */
int readingHead;
int writingHead;

/* declaring the semaphores */
sem_t occuppees;
sem_t libres;

/* declaring the mutex protecting the shifting of the readingHead */
pthread_mutex_t mut;

void *write( void *n );
void *read();

int main (int argc, const char* argv[])
{
    pthread_t writer1;
    pthread_t writer2;
    pthread_t writer3;
    pthread_t reader;

    /* initialize the random generator */
    srand(time(NULL));

    /* initialize the buffer */
    int i = 0;
    readingHead=0;
    writingHead=0;
    for (i=0; i<N; ++i)
        buffer[i]=0;

    /* intialize the semaphores */
    sem_init(&occuppees, 0, 0);
    sem_init(&libres, 0, N);

    /*Create independent threads each of which will execute function*/
    pthread_create(&writer1, NULL, write, (void *) "1" );
    pthread_create(&writer2, NULL, write, (void *) "2" );
    pthread_create(&writer3, NULL, write, (void *) "3" );
    pthread_create(&reader, NULL, read, NULL );

    /* Wait till threads are complete before main continues. */
    pthread_join( writer1, NULL );
    pthread_join( writer2, NULL );
    pthread_join( writer3, NULL );
    pthread_join( reader, NULL );


    exit(EXIT_SUCCESS);
}


void *read()
{
    int i = 0;
    for (i=0; i<15; ++i)
    {
        sleep(2);
        P(occuppees);

        printf("\tlecture: %d - %d\n", readingHead, buffer[readingHead]);
        if (readingHead==N-1)
            readingHead = 0;
        else
            readingHead++;

        V(libres);
    }
}


void *write( void * n )
{
    int i=0;
    for(i=0; i<5; ++i)
    {
        P(libres);
        int value = (int)rand()%10;

        lock(mut);
        buffer[writingHead] = value;

        printf("ecriture %s: %d - %d\n", (char *) n, writingHead, value);

        if (writingHead==N-1)
            writingHead = 0;
        else
            writingHead++;

        unlock(mut);

        V(occuppees);
    }
}

