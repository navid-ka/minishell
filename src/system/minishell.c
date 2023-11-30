/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/30 14:33:05 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	clear_console(void)
{
	printf("\033[2J");
	printf("\033[1;1H");
}
void line_exit(t_mch *sh)
{
	write(2, "exit\n", 5);
	exit(sh->exit);
}

static void	sh_init(t_mch *sh, char **env)
{
	sh->env = NULL;
	sh->parser = NULL;
	ft_memset(&sh->parser, 0, sizeof(t_parser));
	ft_memset(&sh->lex, 0, sizeof(t_env));
	ft_memset(&sh->red, 0, sizeof(t_redir));
	ft_memset(&sh->pipex, 0, sizeof(t_pipe));
	ft_memset(&sh->env, 0, sizeof(t_env));
	get_env(sh, env);
	prompter();
	signals();
}

static void	command_handler(t_mch *sh, char *line)
{
	t_lexer	*lex;
	char	*cmd;

	lex = NULL;
	cmd = clean_input(line);
	main_lexer(cmd, &lex);
	if (check_syntax(lex) != 0)
	{
		sh->exit = 2;
		clear_line(&cmd);
		clear_lexer(&lex);
		return ;
	}
	parser(sh, lex);
	expansor(sh);
	if (bt_is_builtin(sh->parser->args) && sh->pipes == 1)
		exec_bt(sh, sh->parser);
	else
		sh->exit = executor(sh);
	clear_line(&cmd);
	clear_lexer(&lex);
	clear_parser(&sh->parser);
}

void	minishell(t_mch *sh, char **env)
{
	char		*line;
	t_env		*envi;
	char		*prompt;

	line = NULL;
	envi = NULL;
	sh_init(sh, env);
	while (42)
	{
		prompt = shell_prompt(0);
		line = readline(prompt);
		if (!line)
			line_exit(sh);
		if (*line)
		{
			add_history(line);
			if (ft_strncmp(line, "clear", 6) == 0)
				clear_console();
			if (!quote_checker(line))
				syntax_error();
			else
				command_handler(sh, line);
			free_env(&envi);
			clear_line(&prompt);
			clear_line(&line);

		}
	}
}
