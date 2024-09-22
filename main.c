#include <stdio.h>
#include "lib/handle_args.h"

void handle_action(char *action, char *params)
{
	printf("%s : %s\n", action, params);
}
void retrive_handle_action(int count_of_actions, char **actions, char **params)
{
	for (int i = 0; i < count_of_actions; i++)
	{
		printf("%s : %s\n", actions[i], params[i]);
	}
}

int main(int argc, char const *argv[])
{
#ifdef DEBUG
	// simulate the command line arguments with `./main -Da --name "A name" --file file123 p_default -g`
	char const *s_argv[] = {"./main", "-Da", "--name", "A name", "--file", "file123", "p_default", "-gD"};
	handle_args((sizeof(s_argv) / sizeof(char *)), s_argv, handle_action);
	printf("##########################\n");
	retrive_args((sizeof(s_argv) / sizeof(char *)), s_argv, retrive_handle_action);
#else
	handle_args(argc, argv, handle_action);
	printf("##########################\n");
	retrive_args(argc, argv, retrive_handle_action);
#endif
	return 0;
}
