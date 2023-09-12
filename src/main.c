#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *line;

  signals();
  while (1)
	{
		line = readline("MINICONCHA( ͡° ͜ʖ ͡°) > ");
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
		if (!ft_strcmp(line, "pwd"))
			pwd();
		//bt_get_dirs(env, &hola);
		line = clean_input(line);
		printf("%s\n", line);
    signal(SIGINT, sigint_handler);
	}
	free(line);
	return (0);
}
