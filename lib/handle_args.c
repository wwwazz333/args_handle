#include "handle_args.h"

char *concat_with_realloc(char *str1, char *str2, int add_space)
{
	assert(add_space == 1 || add_space == 0);

	char *temp = malloc((strlen(str1) + 1) * sizeof(char));
	strcpy(temp, str1);
	str1 = realloc(str1, (strlen(str1) + strlen(str2) + add_space + 1) * sizeof(char));
	strcpy(str1, temp);
	if (add_space)
		strcat(str1, " ");
	strcat(str1, str2);
	free(temp);
	return str1;
}

/**
 * @param argc number of arguments
 * @param argv arguments
 * @param handle_action function that will handle the action (action, params) params is NULL if there is no params (ex: -e) and action is NULL if it's a default action
 * @brief Handle the arguments passed to the program
 */
void handle_args(int argc, char const **argv, void (*handle_action)(char *, char *))
{

	// skip the name of the program
	argv++;
	argc--;

#ifdef DEBUG
	printf("Starting to handle args (%d args)\n", argc);
#endif

	// stats
	int nbr_long_stats = 0;
	int nbr_short_stats = 0;
	int nbr_default_stats = 0;

	for (int i = 0; i < argc; i++)
	{
		if (strlen(argv[i]) >= 1 && argv[i][0] == '-')
		{
			if (strlen(argv[i]) >= 2 && argv[i][1] == '-') // version long --example 123
			{
				nbr_long_stats++; // stats
				char *action_long = malloc((strlen(argv[i]) - 1) * sizeof(char));
				strcpy(action_long, argv[i] + 2 /*skip '--'*/);

				if (i + 1 >= argc || argv[i + 1][0] == '-') // no params
				{
					handle_action(action_long, NULL);
				}
				else
				{
					char *param = malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
					strcpy(param, argv[i + 1]);
					handle_action(action_long, param);
					free(param);
					i++;
				}
			}
			else // versionc courte -e (each action is one letter)
			{
				int nbr_actions = strlen(argv[i]) - 1;
				char *actions = malloc((nbr_actions + 1) * sizeof(char));
				strcpy(actions, argv[i] + 1 /* skip the '-' */);
				for (int j = 0; j < nbr_actions; j++)
				{
					nbr_short_stats++; // stats
					char action[2] = {actions[j], '\0'};
					handle_action(action, NULL);
				}

				free(actions);
			}
		}
		else // default handle
		{
			nbr_default_stats++; // stats
			char *temp = malloc(sizeof(char) * (strlen(argv[i]) + 1));
			strcpy(temp, argv[i]);
			handle_action(NULL, temp);
			free(temp);
		}
	}

#ifdef DEBUG
	printf("End to handle args (%d long params, %d short params, %d default params)\n", nbr_long_stats, nbr_short_stats, nbr_default_stats);
#endif
}