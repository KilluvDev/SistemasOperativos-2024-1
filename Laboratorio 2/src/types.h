#ifndef TYPES_H
#define TYPES_H

#include <unistd.h>

typedef struct {
    short int id;
    pid_t pid;
    int tell;
    int listen;
} children;

#endif
