/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 19:02:52 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_lexers(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = NULL;
	while (lex)
	{
		free(lex->str);
		lex = lex->next;
		free(tmp);
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
			//parser(sh, lex);
			print_lex_list(lex);
			//TODO:expansor
			//TODO:executor
			signal(SIGINT, sigint_handler);
			line = clean_input(line);
			free(line);
		}
	}
}
