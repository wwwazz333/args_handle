#include <stdio.h>
#include "handle_args.h"

void handle_action(char *action, char *params)
{
	printf("%s : %s\n", action, params);
}

int main(int argc, char const *argv[])
{
	handle_args(argc, argv, handle_action);
	return 0;
}
