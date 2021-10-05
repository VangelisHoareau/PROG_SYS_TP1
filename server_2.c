#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int running =1;

void stop_handler(int sig){
    printf("\nLe numero du signal est : %d\n", sig);
    running=0;
}

int main(){
    printf("coucou\n");
    struct sigaction act;
    act.sa_handler=stop_handler;
    sigaction(SIGINT, &act, NULL);
    while(running){
        printf("pid fils : %d\n", getpid());
        printf("pid père : %d\n", getppid());
        printf("nombre aléatoire : %d\n", (rand()%100));
        sleep(1);
    }
    printf("SUCCES !\n");
    return EXIT_SUCCESS;
}