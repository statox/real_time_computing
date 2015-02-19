#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/* defining macro functions for P() and V() */
#define P(value) sem_wait(&value)
#define V(value) sem_post(&value)

/* defining macro functions for mutexes lock and unlock */
#define lock(value)     pthread_mutex_lock(&value)
#define unlock(value)   pthread_mutex_unlock(&value)

/* defining the number of cases in the waiting zones */
#define N   10
#define M   15

/* defining the number of planes to treat */
#define TOLAND 100
#define TOTAKEOFF 80

/* structure of the waiting zones */
int Air[N];
int Sol[M];

/* reading and writing heads */
int AirR;
int AirW;
int SolR;
int SolW;

/* declaring the semaphores */
sem_t occuppeesAir;
sem_t libresAir;
sem_t occuppeesSol;
sem_t libresSol;

/* declaring the mutex protecting the shifting of the readingHead */
pthread_mutex_t landingStrip;

/* mutex protecting the waiting queues */
pthread_mutex_t mutAir;
pthread_mutex_t mutSol;

void *entrerAir();
void *sortirAir();
void *entrerSol();
void *sortirSol();

int main (int argc, const char* argv[])
{
    pthread_t SortirAvion;
    pthread_t Decollage;
    pthread_t AmenerAvion;
    pthread_t Atterrissage;

    /* initialize the random generator */
    srand(time(NULL));

    /* initialize the buffer */
    int i = 0;
    AirR=0;
    AirW=0;
    SolR=0;
    SolW=0;

    for (i=0; i<N; ++i)
        Air[i]=0;

    for (i=0; i<M; ++i)
        Sol[i]=0;

    /* intialize the semaphores */
    sem_init(&occuppeesAir, 0, 0);
    sem_init(&libresAir, 0, N);
    sem_init(&occuppeesSol, 0, 0);
    sem_init(&libresSol, 0, M);

    /*Create independent threads each of which will execute function*/
    pthread_create(&SortirAvion, NULL, entrerSol, NULL );
    pthread_create(&Decollage, NULL, sortirSol, NULL );
    pthread_create(&AmenerAvion, NULL, entrerAir, NULL );
    pthread_create(&Atterrissage, NULL, sortirAir, NULL );

    /* Wait till threads are complete before main continues. */
    pthread_join( SortirAvion, NULL );
    pthread_join( Decollage, NULL );
    pthread_join( AmenerAvion, NULL );
    pthread_join( Atterrissage, NULL );


    exit(EXIT_SUCCESS);
}



void *entrerAir()
{
    int i=0;
    for(i=0; i<TOLAND; ++i)
    {
        sleep(1);
        P(libresAir);
        int nomAvion = (int)rand()%100;

        lock(mutAir);
        Air[AirW] = nomAvion;

        printf("amener avion: %d - %d\n", AirW, nomAvion);

        if (AirW==N-1)
            AirW = 0;
        else
            AirW++;

        unlock(mutAir);

        V(occuppeesAir);
    }
}


void *entrerSol()
{
    int i=0;
    for(i=0; i<TOTAKEOFF; ++i)
    {
        sleep(1);
        P(libresSol);
        int nomAvion = (int)rand()%100;

        lock(mutSol);
        Sol[SolW] = nomAvion;

        printf("\t\tsortir avion: %d - %d\n", SolW, nomAvion);

        if (SolW==M-1)
            SolW = 0;
        else
            SolW++;

        unlock(mutSol);

        V(occuppeesSol);
    }
}

void *sortirAir()
{
    int i = 0;
    for (i=0; i<TOLAND; ++i)
    {
        sleep(2);
        P(occuppeesAir);
        lock(landingStrip);

        printf("atterrisage: %d - %d\n", AirR, Air[AirR]);
        if (AirR==N-1)
            AirR = 0;
        else
            AirR++;

        unlock(landingStrip);
        V(libresAir);
    }
}

void *sortirSol()
{
    int i = 0;
    for (i=0; i<TOTAKEOFF; ++i)
    {
        sleep(2);
        P(occuppeesSol);
        lock(landingStrip);

        printf("\t\tdecollage: %d - %d\n", SolR, Sol[SolR]);
        if (SolR==M-1)
            SolR = 0;
        else
            SolR++;

        unlock(landingStrip);
        V(libresSol);
    }
}


