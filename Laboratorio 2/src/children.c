#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"

void main_loop(int id, int listen_parent, int tell_parent) {
    int life = 100;
    int attack = 30 + rand() % 11;
    int defense = 10 + rand() % 16;
    int evasion = 60 - defense;

    for(;;) {
        char msg[100];
        read(listen_parent, msg, 100);
        if (strcmp(msg, "exit") == 0) break;
    }
    printf("Player %d is exiting\n", id);
}
