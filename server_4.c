#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int isDead =0;
int running =1;
int code_retour =0;
pid_t pid=0;

void exit_message(){
    printf("Appel a exit_message pour %d donc bye ! \n", getpid());
}

void stop_handler(int sig){
    if (pid==0){
        
    }
    printf("Le numero du signal sur %d est : %d\n",getpid(), sig);
    if (pid!=0){
        kill(pid, SIGTERM);
    }
    atexit(exit_message);
    exit(EXIT_SUCCESS);
}

int main(){
    printf("coucou\n");
    int fds[2];
    pipe(fds);

    pid = fork();
    
    struct sigaction act;
    act.sa_handler=stop_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    
    while(running){
        if (pid==0){
            printf("Le nouveau fork() envoie : \n\tpid fils : %d\n\tpid père : %d\n", getpid(),getppid());
            close(fds[1]);
            int varRandom;
            read(fds[0], &varRandom, sizeof(int));
            printf("\tvarRandom = %d\n", varRandom);
        }
        else{
            printf("Le processus initial envoie : \n\tpid fils : %d\n\tpid père : %d\n", getpid(),getppid());
            int varRandom = rand()%100;
            close(fds[0]);
            write(fds[1], &varRandom, sizeof(int));

            

            // if (code_retour_fils!=0){
            //     printf("\tLe fils s'est arrêté avec un code %d\n", WEXITSTATUS(code_retour_fils));
            // }
            
        }
        sleep(3);
    }
    return code_retour;
}

/*
Question 1.2

Le message s'affiche lorsqu'on met l'option -s INT mais sans kill envoie le signal SIGTERM par défaut qui n'est donc pas traité par le sigaction.
Pour afficher le message, il suffit d'ajouter une reception sigaction(SIGTERM, &act, NULL); dans le main. Cependant sur Mac cela ne fonctionne pas.

Le signal Kill ne peut être traité, il est donc impossible d'afficher le message.
Lorssqu'on donne le processus père :
    - avec -s KILL : la bash est interrompu
    - sans : il ne se passe rien 

Question 1.3

en faisant :
    - CTRL-C : exit_message est appelée
    - kill : exit_message est appelée
    - kill -9 : n'appelle pas exit_message

Question 2-1

En enlevant le changement de la variable running : 
    -le programme ne s'arrête pas avec CTRL-C mais au bout du 2ème le handler est appelé
    - même chose pour kill
    - Kill -9 arrête le processus sans appeler le handler


Pour distinguer les deux messages on peut différencier les PIDs, celui duppliqué avec fork() vaut 0


Le processus fils s'arrête, et seul le père continue.
Dans ps a on peut voir que le processus est toujours existant mais en mode zombie (Z+)

Lorsqu'on tue le père, les deux processus disparaissent.

Question jsp

Lorsqu'on kill le fils, le pere meurt car plus personne à écouter
alors que kill le père n'empêche pas le fils d'ecouter 


*/