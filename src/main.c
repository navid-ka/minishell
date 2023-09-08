#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *line;

	while (1)
	{
		line = readline("MINICONCHA( ͡° ͜ʖ ͡°) > ");
	}
	return (0);
}
