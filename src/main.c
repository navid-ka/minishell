#include "../inc/minishell.h"

int	count_quotes(char *cmd)
{
	int	i;
	int	count;
	int	dquotes;
	int	quotes;

	i = ~0;
	count = 0;
	dquotes = 0;
	quotes = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && !quotes)
			dquotes = (dquotes + 1) % 2;
		else if (cmd[i] == '\'' && !dquotes)
			quotes = (quotes + 1) % 2;
		if ((!quotes && !dquotes) && !(cmd[i] == ' ')
			&& ((cmd[i + 1] == ' ') || !cmd[i + 1]))
			count++;
	}
	return (count);
}

// void create_cmd(char *argv, t_cmd *cmd)
// {
//   int quotes_count;
  
//   quotes_count = 0;
//   quotes_count = count_quotes(argv);
//   cmd->argv = split_cmd(argv, quotes_count);
//   if (!bt_is_builtin(cmd->argv))
//     ft_printf(1, "Env execs?/n");
//   else
//     bt_check_builtin(cmd->argv, NULL);
//     //TODO: aqui debemos hacer algo si no es builtin puede que ejecutarlo desde env?
//   // o quizas me he adelantado y hay que hacer mas cosas
// }


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
	char *line;
  char *prompt;
  //t_cmd cmd;

  get_env(env);
  prompt = shell_prompt();
  prompter();
  rl_catch_signals = 0;
  line = NULL;
  while (1)
	{
    signals();
		line = readline(prompt);
    bt_exit(line);
    if (*line)
    {
		t_token *tok = NULL;
		//create_cmd(line, &cmd);
		if (!syntax_checker(line))
			syntax_error();
		if (ft_strlen(line) > 0)
		add_history(line);
		line = clean_input(line);
		main_lexer(line, &tok);
		print_tokens(tok, line);
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
