#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum arg_type
{
	LONG,
	OTHER
};

void handle_args(int argc, char **argv, void (*handle_action)(char *, char *))
{
	// skip the name of the program
	argv++;
	argc--;

	enum arg_type mode = OTHER;
	char *str_action = NULL;
	char *str_handelling = NULL;

	for (int i = 0; i < argc; i++)
	{
		if (strlen(argv[i]) >= 1 && argv[i][0] == '-')
		{
			if (str_handelling != NULL && strlen(str_handelling) > 0)
			{
				handle_action(str_action, str_handelling);
				free(str_handelling);
				str_handelling = NULL;
				free(str_action);
				str_action = NULL;
			}

			mode = OTHER;
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-')
			{
				mode = LONG;
				str_action = malloc((strlen(argv[i]) - 1) * sizeof(char));
				strcpy(str_action, argv[i] + 2);
				str_handelling = malloc(sizeof(char));
				str_handelling[0] = '\0';
			}
			else
			{
				str_handelling = malloc((strlen(argv[i]) + 1) * sizeof(char));
				strcpy(str_handelling, argv[i] + 2);
				str_action = malloc(2 * sizeof(char));
				strncpy(str_action, argv[i] + 1, 1);
				str_action[1] = '\0';
			}
		}
		else // ne commence pas par '-'
		{
			if (mode == LONG)
			{
				char *temp = malloc((strlen(str_handelling) + strlen(argv[i]) + strlen(" ") + 1) * sizeof(char));
				strcpy(temp, str_handelling);
				strcat(temp, " ");
				strcat(temp, argv[i]);
				free(str_handelling);
				str_handelling = temp;
			}
			else if (mode == OTHER)
			{
				// handle by default
			}
		}
	}
	if (str_handelling != NULL && str_action != NULL)
	{
		handle_action(str_action, str_handelling);
	}

	// Libérer la mémoire allouée à la fin
	if (str_handelling != NULL)
	{
		free(str_handelling);
	}
	if (str_action != NULL)
	{
		free(str_action);
	}
}

void actions(char *action, char *params)
{
	printf("Yes: %s\t : %s\n", action, params);
}

int main(int argc, char **argv)
{
	// simmule un argv qui contiendrais `--action_test test test1 test2 -sShort`
	char *params[] = {"./main", "--action_test", "test", "test1", "test2", "-sShort"};
	// store function in a variable
	handle_args(7, params, actions);
	return 0;
}