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

void	clear_lexer(t_lexer **lexer_list)
{
	t_lexer	*current;

	current = *lexer_list;
	if (lexer_list == NULL || current == NULL)
		return ;
	if (lexer_list)
	{
		while (current->next != NULL)
		{
			current = (*lexer_list)->next;
			free((*lexer_list)->str);
			free(*lexer_list);
			*lexer_list = current;
		}
		free((*lexer_list)->str);
		free(*lexer_list);
	}
}

void	clear_parser(t_parser **parser_list)
{
	t_parser	*current;

	current = *parser_list;
	if (parser_list == NULL || current == NULL)
		return ;
	if (parser_list)
	{
		while (current->next != NULL)
		{
			current = (*parser_list)->next;
			free_tab((*parser_list)->args);
			*parser_list = current;
		}
		free_tab((*parser_list)->args);
		free(*parser_list);
	}
}


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
			print_lex_list(lex);
			sh->parser = convertLexerToParser(lex); //se mueve lex?
			//printParserList(sh->parser); //hacerlo void como proyecto a futuro
			//expansor(sh);
			//print_expansor(sh);
			executor(sh);
			signal(SIGINT, sigint_handler);
			clear_line(&line);
			//clear_lexer(&lex);
			//clear_parser(&sh->parser);
		}
	}
}
