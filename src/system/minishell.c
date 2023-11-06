/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/06 11:36:10 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	clear_console(void)
{
	ft_printf(STDOUT_FILENO, "\033[2J");
	ft_printf(STDOUT_FILENO, "\033[1;1H");
}

static void	sh_init(t_mch *sh, char **env)
{
	sh->env = NULL;
	get_env(sh, env);
	prompter();
	signals();
}

static void command_handler(t_mch *sh, char *line)
{
	t_lexer *lex;
	char	*cmd;

	lex = NULL;
	cmd = clean_input(line);
	main_lexer(cmd, &lex);
	if (check_syntax(lex) != 0)
	{
		add_history(cmd);
		clear_line(&cmd);
		clear_lexer(&lex);
		return ;
	}
	sh->parser = convert_lexer_parser(lex);
	expansor(sh);
	if (ft_strcmp(cmd, ""))
		add_history(cmd);
	executor(sh);
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
	prompt = shell_prompt(0);
	sh_init(sh, env);
	while (42)
	{
		line = readline(prompt);
		if (!line)
			bt_exit(sh, line);
		if (*line)
		{
			if (ft_strncmp(line, "clear", 6) == 0)
				clear_console();
			if (!quote_checker(line))
				syntax_error();
			else
				command_handler(sh, line);
			free_env(&envi);
			clear_line(&line);
		}
	}
}
