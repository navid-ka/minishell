/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/14 17:48:13 by bifrost          ###   ########.fr       */
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

static void	clear_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	minishell(t_mch *sh, char **env)
{
	char	*line;
	t_lexer	*lex;

	sh_init(sh, env);
	lex = NULL;
	line = NULL;
	while (1)
	{
		line = readline(shell_prompt(0));
		bt_exit(line);
		if (*line)
		{
			if (!syntax_checker(line))
				syntax_error();
			add_history(line);
			line = clean_input(line);
			main_lexer(line, &lex);
			// print_lex_list(lex);
			sh->parser = convertLexerToParser(lex); //se mueve lex?
			//printParserList(sh->parser); //hacerlo void como proyecto a futuro
			//expansor(sh);
			//print_expansor(sh);
			executor(sh);
			signal(SIGINT, sigint_handler);
			clear_line(&line);
			clear_lexer(&lex);
			clear_parser(&sh->parser);
		}
	}
}
