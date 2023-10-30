/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/18 15:58:09 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void	sh_init(t_mch *sh, char **env)
{
	sh->env = NULL;
	get_env(sh, env);
	prompter();
	signals();
}

void	minishell(t_mch *sh, char **env)
{
	char		*line;
	t_lexer		*lex;
	t_env		*envi;
	char		*prompt;

	lex = NULL;
	line = NULL;
	envi = NULL;
	prompt = shell_prompt(0);
	sh_init(sh, env);
	while (1)
	{
		line = readline(prompt);
		if (!line)
			bt_exit(sh, line);
		if (*line)
		{
			add_history(line);
			if (!syntax_checker(line))
				syntax_error();
			else
			{
				line = clean_input(line);
				main_lexer(line, &lex);
				sh->parser = convertLexerToParser(lex);
				expansor(sh);
				executor(sh);
				clear_lexer(&lex);
				clear_parser(&sh->parser);
			}
			free_env(&envi);
			//free(prompt);
		}
		clear_line(&line);
	}
}
