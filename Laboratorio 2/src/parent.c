#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "settings.h"
#include "types.h"

void tell_players(children *childrens, char *msg);
int alive_count(children *childrens);
void show_stats(children *childrens);
void ping_players(children *childrens);

/* Main loop */
void make_rounds(children *childrens){
    show_stats(childrens);
    while(alive_count(childrens) > 1){
        tell_players(childrens, "attack 10");
    }
    printf("Game is over\n");
    tell_players(childrens, "exit");
}

void tell_players(children *childrens, char *msg){
    for(int i = 0; i < N_PLAYERS; i++){
        write(childrens[i].tell, msg, MSG_SIZE);
    }
}

int alive_count(children *childrens){
    ping_players(childrens);

    int count = 0;
    for(int i = 0; i < N_PLAYERS; i++){
        if(childrens[i].alive) count++;
    }
    printf("count of alive players: %d\n", count);
    return count;
}

void show_stats(children *childrens){
    tell_players(childrens, "show_stats");
}

void ping_players(children *childrens){
    tell_players(childrens, "ping");
    for(int i = 0; i < N_PLAYERS; i++){
        char msg[MSG_SIZE];
        read(childrens[i].listen, msg, MSG_SIZE);
        if (strcmp(msg, "pong") != 0) {
            childrens[i].alive = false;
        }
    }
}
