#include "../inc/minishell.h"

void free_tokens(t_token *tok)
{
	t_token *tmp;

	tmp = NULL;
	while(tok)
	{
		free(tok->str);
		tok = tok->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *line;

  //signals();
  while (1)
	{
		line = readline("MINICONCHA( ͡° ͜ʖ ͡°) > ");
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
		//bt_get_dirs(env, &hola);
		line = clean_input(line);
		t_token *tok = get_tokens(line);
		if (!ft_strcmp(tok->str, "echo"))
			bt_echo(tok->next);
		// while(tok)
		// {
		// 	printf("str: %s\n type:%d\n\n", tok->str, tok->type);
		// 	tok = tok->next;
		// }
		free_tokens(tok);
    	//signal(SIGINT, sigint_handler);
	}
	free(line);
	return (0);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//tokenizar