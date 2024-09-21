#include <stdio.h>
#include "lib/handle_args.h"

void handle_action(char *action, char *params)
{
	printf("%s : %s\n", action, params);
}

int main(int argc, char const *argv[])
{
#ifdef DEBUG
	// simulate the command line arguments with `./main -Da --name "A name" --file file123 p_default -g`
	char const *s_argv[] = {"./main", "-Da", "--name", "A name", "--file", "file123", "p_default", "-g"};
	handle_args((sizeof(s_argv) / sizeof(char *)), s_argv, handle_action);
#else
	handle_args(argc, argv, handle_action);
#endif
	return 0;
}
