Systèmes temps réel - TP2
Thomas Chekroun - Adrien Fabre

Faire un rapport complet avec les differents cas de tests etc.
EXPORTER EN PDF /!\ /!\

mettre les pseudos codes

Question 1

void *do_work(int duration)
{
    unsigned int i=0;
    while(i< (duration * 320000))
    {
        ++i;
        asm volatile ("nop");
    }
}

la fonction est appellée avec do_work(6000);
On a du faire evoluer le nombre d'itérations dans la boucle while pour qu'elle 
s'execute le temps souhaité.

Question 2
code du handler du signal

void signalHandler(int signum){
    printf ("\nHey! You got a signal %d\n", signum);
}

il faut rajouter la ligne suivante pour pouvoir attraper le signal dans la fonction
main:

    signal (SIGUSR1, signalHandler);

Question 3

On rajoute une execution de la fonction do_work() dans le signal handler pour
simuler un traitement long

En envoyant une rafale de signaux on remarque que tous les signaux envoyés ne
sont pas interceptés.
Celà vient du fait que l'OS utilise un bit à 0 ou à 1 pour indiquer qu'un signal
a été reçu. Ainsi si le traitement du signal est long le bit n'a pas le temps 
d'etre remis à 0 et certains signaux ne sont donc pas "vus".


