#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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
void handle_args(int argc, char **argv, void (*handle_action)(char *, char *))
{
	// skip the name of the program
	argv++;
	argc--;

	for (int i = 0; i < argc; i++)
	{
		if (strlen(argv[i]) >= 1 && argv[i][0] == '-')
		{
			if (strlen(argv[i]) >= 2 && argv[i][1] == '-') // version long --example 123
			{
				char *action_long = malloc((strlen(argv[i]) - 1) * sizeof(char));
				strcpy(action_long, argv[i] + 2 /*skip '--'*/);

				if (i + 1 >= argc || argv[i + 1][0] == '-') // no params
				{
					handle_action(action_long, NULL);
				}
				else
				{
					handle_action(action_long, argv[i + 1]);
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
					char action[2] = {actions[j], '\0'};
					handle_action(action, NULL);
				}

				free(actions);
			}
		}
		else // default handle
		{

			char *temp = malloc(sizeof(char) * (strlen(argv[i]) + 1));
			strcpy(temp, argv[i]);
			handle_action(NULL, temp);
			free(temp);
		}
	}
}