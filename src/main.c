#include "../inc/minishell.h"


void  pr(char *s)
{
  while (*s)
    write(1,s++,1);
}

void prompter(void)
{
  pr("\x1b[35m\n");
  pr("   _     _     _     _     _     _     _     _     _     _  \n");
  pr("  / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\ \n");
  pr(" ( m ) ( i ) ( n ) ( i ) ( c ) ( o ) ( n ) ( c ) ( h ) ( a )\n");
  pr("  \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/ \n");
  pr("\n\n\x1b[0m");
}

char *shell_prompt(void) {
    char *pwd;
    char *prompt;
    char *ansi;
    char *prompt_left;
    char *prompt_right;
    int i;

    pwd = NULL;
    ansi = "\033[0;36m\033[1m";
    pwd = getcwd(pwd, 0);
    i = ft_strlen(pwd) - 1;
    while (i >= 0 && pwd[i] != '/')
        i--;
    if (i >= 0)
        prompt_left = &pwd[i + 1];
    else 
        prompt_left = pwd;
    prompt_right = ft_strjoin(ansi, prompt_left);
    prompt_left = "\033[0m 🔞👅 \x1b[35mConcha( ͡° ͜ʖ ͡°)\n▸ \033[0m";
    prompt = ft_strjoin(prompt_right, prompt_left);
    free(prompt_right);
    free(pwd);
    return (prompt);
}

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
  signals();
  prompter();
  line = NULL;
  while (1)
	{
		line = readline(prompt);
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
		line = clean_input(line);
		t_token *tok = get_tokens(line);
		if (!ft_strcmp(tok->str, "echo"))
			bt_echo(tok->next);
		free_tokens(tok);
    //signal(SIGINT, sigint_handler);
    free(line);
	}
	return (0);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//tokenizar
