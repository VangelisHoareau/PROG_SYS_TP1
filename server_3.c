#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int running =1;

void stop_handler(int sig){
    printf("\nLe numero du signal est : %d\n", sig);
    //running=0;
}

int main(){
    printf("coucou\n");
    pid_t pid = fork();
    struct sigaction act;
    act.sa_handler=stop_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    //sigaction(SIGKILL, &act, NULL);
    while(running){
        if (pid==0){
            printf("Le nouveau fork envoie : \n");
            printf("\tpid fils  : %d\n", getpid());
            printf("\tpid père : %d\n", getppid());
            printf("\tnombre aléatoire : %d\n", (rand()%100));
            sleep(1);
        }
        else{
            printf("Le processus initial envoie : \n");
            printf("\tpid fils : %d\n", getpid());
            printf("\tpid père : %d\n", getppid());
            printf("\tnombre aléatoire : %d\n", (rand()%100));
            sleep(1);
        }
    }
    printf("SUCCES !\n");
    return EXIT_SUCCESS;
}

/*
Question 1.2

Le message s'affiche lorsqu'on met l'option -s INT mais sans kill envoie le signal SIGTERM par défaut qui n'est donc pas traité par le sigaction.
Pour afficher le message, il suffit d'ajouter une reception sigaction(SIGTERM, &act, NULL); dans le main. Cependant sur Mac cela ne fonctionne pas.

Le signal Kill ne peut être traité, il est donc impossible d'afficher le message.
Lorssqu'on donne le processus père :
    - avec -s KILL : la bash est interrompu
    - sans : il ne se passe rien 

En enlevant le changement de la variable running : 
    -le programme ne s'arrête pas avec CTRL-C mais au bout du 2ème le handler est appelé
    - même chose pour kill
    - Kill -9 arrête le processus sans appeler le handler

Question 1.3

Pour distinguer les deux messages on peut différencier les PIDs, celui duppliqué avec fork() vaut 0
Les deux processus s'arrêtent avec 2 appels à CTRL-C , le handler n'est appelé que la première fois
*/