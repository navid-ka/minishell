/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/05 16:49:49 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_lexers(t_mch **sh)
{
	t_lexer *lex;
	t_lexer *l_tmp;
	t_parser *parser;
	t_parser *t_pars;

	lex = (*sh)->lex;
	parser = (*sh)->parser;
	while (lex)
	{
		free(lex->str);
		l_tmp = lex;
		lex = lex->next;
		free(l_tmp);
		l_tmp =  NULL;
	}
}

static void	sh_init(t_mch *sh, char **env)
{
	get_env(sh, env);
	prompter();
	signals();
}

/*static int (t_mch *sh, char *line)
{

	return (0);
}*/

void	minishell(t_mch *sh, char **env)
{
	char	*line;
	t_lexer	*lex;
	(void)sh;

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
			// parser(sh, lex);
			// print_pars_list(sh->parser);
			//expansor(sh);
			//print_expansor(sh);
			//executor(sh);
			t_parser *parserList = convertLexerToParser(lex); //se mueve lex?
			printParserList(parserList);
			//free_lexers(sh);
			signal(SIGINT, sigint_handler);
			line = clean_input(line);
			free(line);
		}
	}
}
