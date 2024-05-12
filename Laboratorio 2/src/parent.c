#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "settings.h"
#include "types.h"

void tell_players(children childrens[N_PLAYERS], char msg[MSG_SIZE]);
int alive_count(children childrens[N_PLAYERS]);
void show_stats(children childrens[N_PLAYERS]);
void ping_players(children childrens[N_PLAYERS]);
void make_players_choose(children childrens[N_PLAYERS]);

/**
 * @brief Bucle principal del proceso padre, gestiona el juego. Se ejecutará hasta que solo quede un jugador.
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 */
void make_rounds(children childrens[N_PLAYERS])
{
    show_stats(childrens);
    while (alive_count(childrens) > 1)
    {
        make_players_choose(childrens);
        ping_players(childrens); // Esperar a que todos los jugadores respondan
        show_stats(childrens);
        if (!childrens[0].alive)
            sleep(1); // Para que no vaya demasiado rápido
    }
    printf("Game is over\n");
    show_stats(childrens);

    if (childrens[0].alive)
    {
        printf("Congratulations, you won!\n");
        exit(0);
    }
    else
    {
        printf("You lost, better luck next time\n");
        if (alive_count(childrens) == 1)
        {
            for (int i = 0; i < N_PLAYERS; i++)
            {
                if (childrens[i].alive)
                {
                    printf("Player %d won\n", i);
                    exit(0);
                }
            }
        }
        else
        {
            int random_winner = rand() % N_PLAYERS;
            printf("There was a draw, player %d won\n", random_winner);
            exit(0);
        }
    }

    tell_players(childrens, "exit");
}

/**
 * @brief Envía un mensaje a todos los jugadores
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 * @param msg El mensaje a enviar
 */
void tell_players(children childrens[N_PLAYERS], char msg[MSG_SIZE])
{
    for (int i = 0; i < N_PLAYERS; i++)
    {
        write(childrens[i].tell, msg, MSG_SIZE);
    }
}

/**
 * @brief Cuenta la cantidad de jugadores que siguen vivos
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 * @return La cantidad de jugadores vivos
 */
int alive_count(children childrens[N_PLAYERS])
{
    ping_players(childrens);

    int count = 0;
    for (int i = 0; i < N_PLAYERS; i++)
    {
        if (childrens[i].alive)
            count++;
    }
    return count;
}

/**
 * @brief Indica a cada jugador que muestre sus estadísticas
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 */
void show_stats(children childrens[N_PLAYERS])
{
    printf("\n##################### Showing stats #####################\n");

    tell_players(childrens, "show_stats");
    ping_players(childrens); // Esperar a que todos los jugadores respondan

    printf("#########################################################\n\n");
}

/**
 * @brief Envía un ping a todos los jugadores para comprobar si siguen vivos. Como efecto secundario, también se puede utilizar para sincronizar a los jugadores.
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 */
void ping_players(children childrens[N_PLAYERS])
{
    tell_players(childrens, "ping");
    for (int i = 0; i < N_PLAYERS; i++)
    {
        char msg[MSG_SIZE];
        read(childrens[i].listen, msg, MSG_SIZE);
        if (strcmp(msg, "pong") != 0)
        {
            childrens[i].alive = false;
        }
    }
}

/**
 * @brief Hace que cada jugador elija a quién atacar
 *
 * @details Se le pedirá al primer jugador que elija a quién atacar, luego se le pedirá a los demás jugadores que elijan a quién atacar.
 * Si un jugador está muerto, no se le pedirá que elija.
 * Después de que todos los jugadores hayan elegido, el padre enviará las elecciones a los respectivos objetivos.
 *
 * @param childrens El array de procesos hijos, con sus respectivas tuberías
 */
void make_players_choose(children childrens[N_PLAYERS])
{
    ping_players(childrens); // Sincroniza y actualiza los estados de los jugadores
    char msg[MSG_SIZE] = "choose ";

    for (int i = 0; i < N_PLAYERS; i++)
    {
        if (childrens[i].alive)
        {
            char temp[10];
            sprintf(temp, "%d ", childrens[i].id);
            strcat(msg, temp);
        }
    }

    char user_msg[MSG_SIZE];
    if (childrens[0].alive)
    {
        write(childrens[0].tell, msg, MSG_SIZE);
        read(childrens[0].listen, user_msg, MSG_SIZE);
    }

    int target;
    int attack;

    for (int i = 1; i < N_PLAYERS; i++)
    {
        if (childrens[i].alive)
        {
            write(childrens[i].tell, msg, MSG_SIZE);
        }
    }

    if (childrens[0].alive)
    {
        sscanf(user_msg, "attack %d %d", &attack, &target);
        write(childrens[target].tell, user_msg, MSG_SIZE);
    }
    for (int i = 1; i < N_PLAYERS; i++)
    {
        if (childrens[i].alive)
        {
            read(childrens[i].listen, msg, MSG_SIZE);
            sscanf(msg, "attack %d %d", &attack, &target);
            write(childrens[target].tell, msg, MSG_SIZE);
        }
    }
}
