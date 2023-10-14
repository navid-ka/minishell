/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/15 00:50:19 by bifrost          ###   ########.fr       */
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

	lex = NULL;
	line = NULL;
	envi = NULL;
	sh_init(sh, env);
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
			expansor(sh);
			//print_expansor(sh);
			executor(sh);
			signal(SIGINT, sigint_handler);
			clear_lexer(&lex);
			//clear_parser(&sh->parser);
			free_env(&envi);
			clear_line(&line);
		}
	}
}
