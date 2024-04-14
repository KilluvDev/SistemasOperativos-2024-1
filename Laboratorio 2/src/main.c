#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "types.h"

int main(){
    short int n_players = 4;
    short int id = n_players;

    children childrens[n_players];

    int listen_parent, tell_parent;

    while(id--){
        int pipe_p2c[2], pipe_c2p[2];
        pipe(pipe_p2c);
        pipe(pipe_c2p);

        pid_t pid_children = fork();

        if(pid_children == 0){
            listen_parent = pipe_p2c[0];
            close(pipe_p2c[1]);

            tell_parent = pipe_c2p[1];
            close(pipe_c2p[0]);
            break;
        }

        childrens[id].id = id;
        childrens[id].pid = pid_children;

        childrens[id].tell = pipe_p2c[1];
        close(pipe_p2c[0]);

        childrens[id].listen = pipe_c2p[0];
        close(pipe_c2p[1]);
    }
    srand(time(NULL) + id);

    player stats;

    if (id >= 0) {
        stats.life = 100;
        stats.attack = 30 + rand() % 11;
        stats.defense = 10 + rand() % 16;
        stats.evasion = 60 - stats.defense;
    }

    if (id == -1) {
        for(int i = 5; i >= 0; i--){
            printf("%d\n", i);
            sleep(1);
            if (i == 0) {
                for (int j = 0; j < n_players; j++) {
                    char *msg = "exit";
                    write(childrens[j].tell, msg, strlen(msg) + 1);
                }
            }
        }
    } else {
        for(;;) {
            char msg[100];
            read(listen_parent, msg, 100);
            if (strcmp(msg, "exit") == 0) {
                printf("Player %d is exiting\n", id);
                break;
            }
        }
    }

    while(wait(NULL) > 0);
    return 0;
}
