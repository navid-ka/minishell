/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 14:59:30 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens(t_token *tok)
{
	t_token *tmp;

	tmp = NULL;
	while (tok)
	{
		free(tok->str);
		tok = tok->next;
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
	t_token	*tok;
	(void)sh;

	sh_init(sh, env);
	tok = NULL;
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
			main_lexer(line, &tok);
			symbol_sorter(tok);
			parser(sh, tok);
			print_tok_list(tok);
			//TODO:expansor
			//TODO:executor
			signal(SIGINT, sigint_handler);
			line = clean_input(line);
			free(line);
		}
	}
}
