#ifndef TYPES_H
#define TYPES_H

#include <unistd.h>
#include <stdbool.h>

typedef struct {
    short int id;
    pid_t pid;
    int tell;
    int listen;
    bool alive;
} children;

#endif
