#ifndef HANDEL_ARGS_HEADER
#define HANDEL_ARGS_HEADER

#ifndef DEBUG
#define DEBUG 0
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void handle_args(int argc, char const **argv, void (*handle_action)(char *, char *));

#endif