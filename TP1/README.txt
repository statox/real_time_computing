Systèmes temps réel - TP1
Thomas Chekroun - Adrien Fabre

Faire un rapport complet avec les differents cas de tests etc.
EXPORTER EN PDF /!\ /!\

mettre les pseudos codes

Exercice 1
##########
Question 1
cf. exercice1.c

Exercice 2
##########
Question 2
cf. exercice2.c

Exercice 3
##########
Questions 3/4

On a une buffer de N cases.
Le lecteur peut lire les cases écrites
L'ecrivain peut écrire dans les cases vides.

Les deux threads peuvent s'executer en même temps.

on met un semaphore sur les cases occupées et un sur les cases libres.
Le semaphore occuppees est initialisé à 0. Pour représenter le fait qu'au
début de l'exécution toutes les cases sont vides.
Le semaphore vides est intialisé à N pour représenter le fait qu'au début de
l'exécution toutes les cases sont disponibles à la lecture.

De plus pour modéliser notre buffer nous avons besoin d'une tête de lecture et
d'une tête d'écriture. Ces têtes seront des pointeurs indiquant sur quelles
cases les processus peuvent effectuer leurs actions.
Ces pointeurs sont tous les deux initialisés à 0 car la lecture et l'écriture
se font en partant de la première case du buffer.


Les implémentations sont les suivantes:
Thread ecriture:œ

Pour i allant de 0 à nombre d'écritures souhaitées
    P(libres)
    
    lock(mutex)
    
    ecrire dans buffer au niveau de la tete d'écriture
    déplacer la tête d'écriture à la case suivante
    
    unlock(mutex)

    V(occuppées)
FinPour

Dans ce processus on effectue un P(libres) pour ne commencer l'écriture
que si une case est disponible pour être remplie.
Et une fois l'écriture effectue on effectue un V(libres) pour indiquer 
au lecteur qu'il a une case à lire.

L'exclusion mutuelle permet de protéger la lecture et le déplacement de la 
tête de lecture dans le cas où plusieurs écrivains concurents

Thread lecture:

Pour i allant de 0 à nombre de lectures souhaitées
    P(occuppées)
    
    lire dans le buffer au niveau de la tete de lecture
    déplacer la tête de lecture à la case suivante
    
    V(libres)
FinPour

Dans le processus de lecture, on effectue un P(occuppees) pour ne commencer
la lecture que si une case contient une donnée à lire.
Et inversement une fois la case lu on signale à l'écrivain qu'une nouvelle
case est disponible à l'écriture.

Question 5
cf. exercice3.c pour le problème avec 1 lecteur et 1 écrivain et
cf. exercice3.1.c pour le problème avec 1 lecteur et 3 écrivains.

Exercice 4
##########

Question 6
Le problème de type exclucion mutuelle est lié à la piste 
d'atterissage/décollage. En efffet les threads permettant d'atterir
et de décoller doivent pas pouvoir utiliser cette piste en même temps.

Le problème de type producteur/consommateur est lié aux zones d'attentes:
Lorsque ces zones sont pleines il faut attendre qu'un avion en sorte avant
de pouvoir en rajouter un nouveau.

Nous aurons besoin de 
1 mutex, initialisée à 1. Elle permettra aux threads d'atterrissage et de 
décollage de ne pas utiliser la même piste.

Il faudra également 4 sémaphores:
il y en aura 2 par zones d'attentes en se basant sur les mêmes que le buffer 
de l'exercice précédent 
Air:    occuppeesAir intialisé à 0
        libresAir initialisé à N
Sol:    occuppeesSol intialisé à 0
        libresSol initialisé à M

Question 7
Processus existants:
entrerAir, entrerSol, sortirAir, sortirSol

AmenerAvion:
Pour i de 0 au nombre d'avions total en l'air
    P(libresAir)

    lock(mutAir)
    Air[AirWritingHead] = nouvelAvion
    Décalage de AirWritingHead

    unlock(mutAir)

    V(occuppeesAir)
FinPour

SortirAvion:
Pour i de 0 au nombre d'avions total au sol
    P(libresSol)

    lock(mutSol)
    Sol[SolWritingHead] = nouvelAvion
    Décalage de SolWritingHead

    unlock(mutSol)

    V(occuppeesSol)
FinPour

Atterrissage:
Pour i de 0 au nombre d'avions total en l'air
    P(occuppeesAir)
    lock(pisteAtterrissage)
    
    Décalage de AirReadingHead

    unlock(pisteAtterrissage)
    V(libresAir)
FinPour

Decollage:
Pour i de 0 au nombre d'avions total au sol
    P(occuppeesSol)
    lock(pisteAtterrissage)
    
    Décalage de SolReadingHead

    unlock(pisteAtterrissage)
    V(libresSol)
FinPour


