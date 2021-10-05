#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("coucou\n");
    while(1){
        printf("pid fils : %d\n", getpid());
        printf("pid père : %d\n", getppid());
        printf("nombre aléatoire : %d\n", (rand()%100));
        sleep(3);
    }
    printf("coucou2");
    return EXIT_SUCCESS;
}