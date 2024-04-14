#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "types.h"

void make_rounds(children *childrens, short int n_players){
    for(int i = 5; i > 0; i--){
        printf("%d\n", i);
        sleep(1);
    }

    for (int j = 0; j < n_players; j++) {
        char *msg = "exit";
        write(childrens[j].tell, msg, strlen(msg) + 1);
    }

    printf("Parent is exiting\n");
}
