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
 * @param handle_action function that will handle the action (all_actions, all_params) params is NULL if there is no params (ex: -e) and action is NULL if it's a default action. This function will be called at the end of the retrive_args function with all the actions and params (but will avoid multiple call of the same action, and keep only the first one)
 * @post actions_retrived and params_retrived are filled with the actions and params (same length)
 */
void retrive_args(int argc, char const **argv, void (*handle_action)(int, char **, char **));

#endif