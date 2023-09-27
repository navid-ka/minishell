/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:39:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/27 11:03:35 by nkeyani-         ###   ########.fr       */
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
	get_env(env);
	prompter();
	signals();
}

static int if_line(t_mch *sh, char *line)
{
	symbol_sorter(sh->tok);
	parser(sh);
	if (!syntax_checker(line))
		syntax_error();
	add_history(line);
	line = clean_input(line);
	main_lexer(line, &tok);
}

}

void	minishell(t_mch *sh, char **env)
{
	char	*line;
	t_token	*tok;

	sh_init(env);
	tok = NULL;
	line = NULL;
	while (1)
	{
		line = readline(shell_prompt(0));
		bt_exit(line);
		if (*line)
		{
			if_line(sh);
			signal(SIGINT, sigint_handler);
			free(line);
		}
	}
}
