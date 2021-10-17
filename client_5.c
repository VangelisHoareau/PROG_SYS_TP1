#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int running=1;
int fd;

void stop_handler(int sig){
    printf("\nOn s'arrête avec un signal numéro %d!!\n", sig);
    close(fd);
    exit(EXIT_SUCCESS);
}

int main() {
    char chaineRandom[1000];
    fd = open("fifo", O_RDONLY);

    struct sigaction act;
    act.sa_handler=stop_handler;
    sigaction(SIGPIPE, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

   while (running) {
        usleep(1100000);
        if(read(fd, chaineRandom, 1000)==0){
            printf("On s'arrête !!");
            return EXIT_SUCCESS;
        }
        else{
            printf("Le serveur envoie : %s\n", chaineRandom);
        }
        // fgets(chaineRandom, 3, fd);
        // printf("%s",chaineRandom);
   }
}