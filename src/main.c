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
  char *prompt;

  prompt = shell_prompt();
  prompter();
  line = NULL;
  while (1)
	{
    signals();
		line = readline(prompt);
    bt_exit(line);
    if (*line)
    {
		  if (!syntax_checker(line))
			  syntax_error();
		  if (ft_strlen(line) > 0)
            add_history(line);
		  line = clean_input(line);
		  t_token *tok = get_tokens(line);
		  if (!ft_strcmp(tok->str, "echo"))
			  bt_echo(tok->next);
		  free_tokens(tok);
      signal(SIGINT, sigint_handler);
      free(line);
    }
	}
	return (0);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//tokenizar
