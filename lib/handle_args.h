#ifndef HANDEL_ARGS_HEADER
#define HANDEL_ARGS_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @param argc number of arguments
 * @param argv arguments
 * @param handle_action function that will handle the action (action, params) params is NULL if there is no params (ex: -e) and action is NULL if it's a default action
 * @brief Handle the arguments passed to the program
 */
void handle_args(int argc, char const **argv, void (*handle_action)(char *, char *));

/**
 * @param argc number of arguments
 * @param argv arguments
 * @post actions_retrived and params_retrived are filled with the actions and params (same length)
 */
void retrive_args(int argc, char const **argv, void (*handle_action)(int, char **, char **));

#endif