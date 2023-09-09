#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *line;

	while (1)
	{
		line = "\n";
		line = readline("MINICONCHA( ͡° ͜ʖ ͡°) > ");
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
		if (!ft_strcmp(line, "pwd"))
			pwd();
	}
	free(line);
	return (0);
}
