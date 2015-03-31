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


Question 6 
Sleep : on fait une pause avec usleep(500 ms) et un travail de 500ms avec do_work du coup tache periodique de 1s ( 500 + 500)
Alarm : alarm(1) => envoie un signal SIGALRM au bout d'une seconde, on catch le signal avec pause() qui endors le thread jusqu'a la reception d'un signal,
	Entre l'appel d'alarm() et pause() on fait notre do_work. Par défaut SIGALRM tue le process il faudrai donc rajouter un signal handler pour changer 
	ce comportement
Problèmes : Appel à des fonctions externes du coup risque de décallage dans le temps.

Question 7 :
Timer : Tache périodique, fonction start timer qui permet de creer notre timer, on crée la valeur de notre timer ( struct itimerspec ) prend 2 arguments si on veut un 
timer de façon infini il faut mettre les deux variables à la même valeur, value= 0 le timer se lancera jamais, si intervalle a 0 il ne se lancera qu'une seule fois
on appel ensuite timer create, et settime pour lui attribuer les attributs définis.
toute les secondes le timer va lancer un SIGALARM qui va appeler la methode timer_callBack() et va faire notre do_work.

Question 8 : sur 12 secondes Regarder la picture

Question 9 : Problème les processus vont s'exécuter avant leur réactivation donc utilisation de pause et des signaux pour sortir de la pause
