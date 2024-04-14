#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "settings.h"
#include "types.h"
#include "parent.h"
#include "children.h"

int main(){
    short int id = N_PLAYERS;

    children childrens[N_PLAYERS];

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

    // Seed for random numbers
    srand(time(NULL) + id);

    if (id == -1) {
        // Parent
        make_rounds(childrens);
    } else {
        // Players
        main_loop(id, listen_parent, tell_parent);
    }

    while(wait(NULL) > 0);
    return 0;
}
