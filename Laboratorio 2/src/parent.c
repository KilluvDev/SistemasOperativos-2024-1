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

void make_rounds(children childrens[N_PLAYERS])
{
    /*
    Función make_rounds.
    tipo void.
    *****
    Parámetros:
    childen childrens[N_PLAYERS]

    children childrens[N_PLAYERS] es un array del struct children
    *****

    *****
    Sin retorno.
    */
    show_stats(childrens);
    while (alive_count(childrens) > 1)
    {
        make_players_choose(childrens);
        ping_players(childrens); // Wait for all players
        show_stats(childrens);
        if (!childrens[0].alive)
            sleep(1); // So it doesnt go too fast
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

void tell_players(children childrens[N_PLAYERS], char msg[MSG_SIZE])
{
    /*
    Función tell_players.
    tipo void.
    *****
    Parámetros:
    children childrens[N_PLAYERS]
    char msg[MSG_SIZE]

    children childrens[N_PLAYERS] es el array del struct
    char msg[MSG_SIZE] es el mensaje entre hijos
    *****
    La función se comunica entre hijos
    *****
    Sin retorno.
    */
    for (int i = 0; i < N_PLAYERS; i++)
    {
        write(childrens[i].tell, msg, MSG_SIZE);
    }
}

int alive_count(children childrens[N_PLAYERS])
{
    /*
    Función alive_count.
    tipo int.
    *****
    Parámetros:
    children childrens[N_PLAYERS]

    children childrens[N_PLAYERS] es el arreglo del struct de children.
    *****
    La función cuenta la cantidad de jugadores restantes.
    *****
    Retorna la cantidad de jugadores.
    */
    ping_players(childrens);

    int count = 0;
    for (int i = 0; i < N_PLAYERS; i++)
    {
        if (childrens[i].alive)
            count++;
    }
    return count;
}

void show_stats(children childrens[N_PLAYERS])
{
    /*
    Función show_stats.
    tipo void.
    *****
    Parámetros:
    children childrens[N_PLAYERS]

    children childrens[N_PLAYERS] es el arreglo del struct de children.
    *****
    La función muestra el estatus de cada jugador
    *****
    Sin retorno.
    */
    printf("\n##################### Showing stats #####################\n");

    tell_players(childrens, "show_stats");
    ping_players(childrens); // Wait for all players

    printf("#########################################################\n\n");
}

void ping_players(children childrens[N_PLAYERS])
{
    /*
    Función ping_players.
    tipo void.
    *****
    Parámetros:
    children childrens[N_PLAYERS]

    children childrens[N_PLAYERS] es el arreglo del struct de children.
    *****
    La funcion revisa los jugadores y los sincroniza para el efecto del juego
    *****
    Sin retorno.
    */
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

void make_players_choose(children childrens[N_PLAYERS])
{
    /*
    Función make_players_choose.
    tipo void.
    *****
    Parámetros:
    children childrens[N_PLAYERS]

    children childrens[N_PLAYERS] es el arreglo del struct de children.
    *****
    La función efectúa los cambios de estados entre los jugadores.
    *****
    Sin retorno.
    */
    ping_players(childrens); // Sinc and update alive status
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
