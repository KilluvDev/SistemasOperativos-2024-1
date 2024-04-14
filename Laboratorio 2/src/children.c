#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "settings.h"
#include "types.h"

bool starts_with(const char *pre, const char *str);

void main_loop(int id, int listen_parent, int tell_parent) {
    int life = 100;
    int attack = 30 + rand() % 11;
    int defense = 10 + rand() % 16;
    int evasion = 60 - defense;

    char msg[MSG_SIZE];
    while(1) {
        if (life <= 0) break;
        read(listen_parent, msg, MSG_SIZE);

        if (strcmp(msg, "exit") == 0) {
            break;
        }

        if (strcmp(msg, "ping") == 0) {
            write(tell_parent, "pong", MSG_SIZE);
            continue;
        }

        if (strcmp(msg, "show_stats") == 0) {
            printf("Player %d: %d(HP) %d(AP) %d %d\n", id, life, attack, defense, evasion);
            continue;
        }

        if (starts_with(msg, "attack") == 0) {
            int received_damage;
            sscanf(msg, "attack %d", &received_damage);
            life -= received_damage;
            printf("Player %d received %d damage\n", id, received_damage);
            continue;
        }
    }

    printf("Player %d is dead\n", id);

    while(1) {
        // Wait for parent to send exit message

        if (strcmp(msg, "exit") == 0) {
            break;
        }
        if (strcmp(msg, "ping") == 0) {
            write(tell_parent, "dead", MSG_SIZE);
        }

        read(listen_parent, msg, MSG_SIZE);
    }

    close(listen_parent);
    close(tell_parent);
    printf("Player %d is exiting\n", id);
}

bool starts_with(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre
            ? false
            : strncmp(pre, str, lenpre) == 0;
}
