#include "handle_args.h"

char *concat_with_realloc(char *str1, char *str2, int add_space)
{
	assert(add_space == 1 || add_space == 0);

	str1 = realloc(str1, (strlen(str1) + strlen(str2) + add_space + 1) * sizeof(char));
	if (add_space)
		strcat(str1, " ");
	strcat(str1, str2);
	return str1;
}

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

				free(action_long);
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

char **actions_retrived = NULL;
char **params_retrived = NULL;
int count_of_actions = 0;

void _retrive_handle_action(char *action, char *param)
{
	actions_retrived = realloc(actions_retrived, (count_of_actions + 1) * sizeof(char *));
	params_retrived = realloc(params_retrived, (count_of_actions + 1) * sizeof(char *));
	if (action != NULL)
	{
		actions_retrived[count_of_actions] = malloc(sizeof(char) * (strlen(action) + 1));
		strcpy(actions_retrived[count_of_actions], action);
	}
	else
	{
		actions_retrived[count_of_actions] = NULL;
	}

	if (param != NULL)
	{
		params_retrived[count_of_actions] = malloc(sizeof(char) * (strlen(param) + 1));
		strcpy(params_retrived[count_of_actions], param);
	}
	else
	{
		params_retrived[count_of_actions] = NULL;
	}
	count_of_actions++;
}

void retrive_args(int argc, char const **argv, void (*handle_action)(int, char **, char **))
{
	// stats
	int count_of_actions_in_double_stats = 0;

	handle_args(argc, argv, _retrive_handle_action);

	// post treatment of action to avoid multiple call of the same action
	for (int i = 0; i < count_of_actions; i++)
	{
		if (actions_retrived[i] != NULL)
		{
			for (int j = i + 1; j < count_of_actions; j++)
			{
				// if the action is the same
				if (actions_retrived[j] != NULL && strcmp(actions_retrived[i], actions_retrived[j]) == 0)
				{
					count_of_actions_in_double_stats++; // stats
					// free the action and the param
					free(actions_retrived[j]);
					free(params_retrived[j]);

					// move the last element to the current position
					actions_retrived[j] = actions_retrived[count_of_actions - 1];
					params_retrived[j] = params_retrived[count_of_actions - 1];

					// set the last element to NULL
					actions_retrived[count_of_actions - 1] = NULL;
					params_retrived[count_of_actions - 1] = NULL;

					// decrement the count of actions
					count_of_actions--;
				}
			}
		}
	}

#ifdef DEBUG
	printf("End to retrive args (%d actions in double)\n", count_of_actions_in_double_stats);
#endif

	// call the handle_action function
	handle_action(count_of_actions, actions_retrived, params_retrived);

	// free all memory
	for (int i = 0; i < count_of_actions; i++)
	{
		if (actions_retrived[i] != NULL)
		{
			free(actions_retrived[i]);
		}
		if (params_retrived[i] != NULL)
		{
			free(params_retrived[i]);
		}
	}
	free(actions_retrived);
	actions_retrived = NULL;
	free(params_retrived);
	params_retrived = NULL;

	count_of_actions = 0;
}