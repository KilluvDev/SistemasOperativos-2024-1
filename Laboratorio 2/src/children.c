#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "settings.h"
#include "types.h"

bool starts_with(const char *pre, const char *str);
void extract_ints_from_string(char msg[MSG_SIZE], int list[N_PLAYERS], int *alive, int skip);
bool check_valid_target(int target, int players[N_PLAYERS], int alive);

/**
 * @brief Main loop of the child process, listens to the parent and reacts to each message
 *
 * @param id The id of the child
 * @param listen_parent The file descriptor to listen to the parent
 * @param tell_parent The file descriptor to tell the parent
 */
void main_loop(int id, int listen_parent, int tell_parent)
{
    int life = 100;
    int attack = 30 + rand() % 11;
    int defense = 10 + rand() % 16;
    int evasion = 60 - defense;

    char msg[MSG_SIZE];
    while (1)
    {
        if (life <= 0)
            break;
        read(listen_parent, msg, MSG_SIZE);

        if (strcmp(msg, "exit") == 0)
        {
            break;
        }

        if (strcmp(msg, "ping") == 0)
        {
            write(tell_parent, "pong", MSG_SIZE);
            continue;
        }

        if (strcmp(msg, "show_stats") == 0)
        {
            if (id)
            {
                // Bot
                printf("Player (%d): %d HP | %d Attack | %d Defence | %d%% Evasión\n", id, life, attack, defense, evasion);
            }
            else
            {
                // User
                printf("Your stats: %d HP | %d Attack | %d Defence | %d%% Evasion\n", life, attack, defense, evasion);
            }
            continue;
        }

        if (starts_with(msg, "choose "))
        {
            int players[N_PLAYERS];
            int alive;
            extract_ints_from_string(msg, players, &alive, id);
            int target;

            if (id > 0)
            {
                // Bot
                target = players[rand() % alive];
                printf("Player %d chose to attack player %d\n", id, target);
            }
            else
            {
                // User
                char text[100];
                sprintf(text, "Choose a player to attack (%d", players[0]);
                for (int i = 1; i < alive && i > 0; i++)
                {
                    char temp[10];
                    sprintf(temp, ", %d", players[i]);
                    strcat(text, temp);
                }
                strcat(text, "): ");
                printf("%s ", text);
                scanf("%d", &target);
                while (!check_valid_target(target, players, alive))
                {
                    printf("Invalid target, choose again: ");
                    scanf("%d", &target);
                }
                printf("\n");
            }
            sprintf(msg, "attack %d %d %d", attack, target, id);
            write(tell_parent, msg, MSG_SIZE);
            continue;
        }

        if (starts_with(msg, "attack"))
        {
            int received_damage;
            int target;
            int from;
            sscanf(msg, "attack %d %d %d", &received_damage, &target, &from);

            if (rand() % 100 < evasion)
            {
                printf("Player %d evaded the attack from player %d\n", id, from);
                continue;
            }
            int damage = received_damage - defense;
            if (damage < 0)
                damage = 0;
            life -= damage;
            printf(
                "Player %d received %d (%d-%d) damage from player %d, leaving him with %d HP\n",
                id,
                damage,
                received_damage,
                defense,
                from,
                life);
            continue;
        }

        printf("Player %d received unknown message: %s\n", id, msg);
    }

    printf("Player %d is dead\n", id);

    while (1)
    {
        // Wait for parent to send exit message

        if (strcmp(msg, "exit") == 0)
        {
            break;
        }
        if (strcmp(msg, "ping") == 0)
        {
            write(tell_parent, "dead", MSG_SIZE);
        }

        read(listen_parent, msg, MSG_SIZE);
    }

    close(listen_parent);
    close(tell_parent);
}

/**
 * @brief Checks if a message starts with a certain string
 *
 * @param msg The message to check
 * @param str The string to check if the message starts with
 * @return true
 * @return false
 */
bool starts_with(const char msg[MSG_SIZE], const char *str)
{
    size_t lenmsg = strlen(msg),
           lenstr = strlen(str);
    return lenmsg < lenstr
               ? false
               : (strncmp(msg, str, lenstr) == 0);
}

/**
 * @brief Extracts the integers from a string
 *
 * @param msg The message to extract the integers from
 * @param list The list to store the integers
 * @param alive The number of integers extracted
 * @param skip The number to skip
 */
void extract_ints_from_string(char msg[MSG_SIZE], int list[N_PLAYERS], int *alive, int skip)
{
    char *c = msg;
    int i = 0;
    *alive = 0;
    while (*c)
    {
        if (isdigit(*c))
        {
            int number = strtol(c, &c, 10);
            if (number == skip)
                continue;
            list[i] = number;
            i++;
            (*alive)++;
        }
        else
        {
            c++;
        }
    }
}

/**
 * @brief Checks if the target is in the list of players
 *
 * @param target The target to check
 * @param players The list of players
 * @param alive The number of alive players
 * @return true
 * @return false
 */
bool check_valid_target(int target, int players[N_PLAYERS], int alive)
{
    for (int i = 0; i < alive; i++)
    {
        if (players[i] == target)
            return true;
    }
    return false;
}
