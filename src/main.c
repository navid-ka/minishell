#include "../inc/minishell.h"

void  pr(char *s)
{
  while (*s)
    write(1,s++,1);
}

void prompter(void)
{
  #define MAGENTA 
  pr("\x1b[35m\n");
  pr("   _     _     _     _     _     _     _     _     _     _  \n");
  pr("  / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\ \n");
  pr(" ( m ) ( i ) ( n ) ( i ) ( c ) ( o ) ( n ) ( c ) ( h ) ( a )\n");
  pr("  \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/ \n");
  pr("\n\n\x1b[0m");
}

char *shell_prompt(void)
{
  char *pwd;
  char *prompt;
  char *ansi;
  char *prompt_left;
  char *prompt_right;

  pwd = NULL;
  ansi = "\033[0;36m\033[1m";
  prompt_left = " 🔞👅 Concha( ͡° ͜ʖ ͡°)\n▸\033[0m";
  prompt_right = ft_strjoin(ansi, getcwd(pwd, 0));
  prompt = ft_strjoin(prompt_right, prompt_left);
  free(prompt_right);
  free(pwd);
  return (prompt);
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
  while (1)
	{
		line = readline(prompt);
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
            add_history(line);
		/*if (!ft_strcmp(line, "pwd"))
			bt_pwd();*/
		//bt_get_dirs(env, &hola);
		line = clean_input(line);
		printf("%s\n", line);
    signal(SIGINT, sigint_handler);
	}
	free(line);
	return (0);
}
