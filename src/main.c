#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *line;

	using_history();
	while (1)
	{
		line = "\n";
		line = readline(line);
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
	}
	free(line);
	return (0);
}
