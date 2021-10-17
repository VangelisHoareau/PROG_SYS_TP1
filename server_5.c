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
    char chaineRandom[3];
    int varRandom;
    mkfifo("fifo", 0666);
    fd = open("fifo", O_WRONLY);

    struct sigaction act;
    act.sa_handler=stop_handler;
    sigaction(SIGPIPE, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

   while (running) {
        varRandom = rand()%100;
        sprintf(chaineRandom, "%d", varRandom);
        write(fd, chaineRandom, sizeof(char[3]));
        write(fd, "\n", sizeof(char*));
        usleep(1000000);
   }
}