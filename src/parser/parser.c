/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 01:39:58 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/17 17:53:25 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_cmd_args(t_lexer *tmp, t_parser *parser)
{
    t_lexer *lex;
    int i = 0;
    int skip_redir = 0;

    lex = tmp;
    if (!parser->args)
        return;
    while (lex && lex->type != PIPE)
    {
        if (lex->type == CMD && !is_redir(lex->type) && !skip_redir)
        {
            parser->args[i] = ft_strdup(lex->str);
            i++;
        }
        else if (is_redir(lex->type))
            skip_redir = 1;
        else if (skip_redir && !is_redir(lex->type))
            skip_redir = 0;
        lex = lex->next;
    }
    parser->args[i] = NULL;
    lex = tmp;
}

void	process_redirections(t_lexer *tmp, t_parser *parser)
{
    t_redir *new_redir;
	int		type;

	type = tmp->type;
    tmp = tmp->next;
    new_redir = create_redir_node(tmp->str, type);
    redir_lstadd_back(&(parser->redir_list), new_redir);
}

void process_tokens(t_mch *sh, t_lexer *tmp, t_parser *parser)
{
	t_lexer *start;

	start = tmp;
	while (tmp != NULL)
	{
		if (tmp && tmp->type == PIPE)
		{
			parser_lstadd_back(&(sh->parser), parser);
			parser = create_parser();
			tmp = tmp->next;
			start = tmp;
			continue;
		}
		if (parser->args)
			free_tab(parser->args);
		parser->args = (char **)ft_calloc((count_words(start) + 1), sizeof(char *));
		if (!is_redir(tmp->type))
			process_cmd_args(start, parser);
		else if (is_redir(tmp->type))
			process_redirections(tmp, parser);
		tmp = tmp->next;
	}
	parser_lstadd_back(&(sh->parser), parser);
}

void parser(t_mch *sh, t_lexer *lex)
{
	t_lexer *tmp;
	t_parser *parser;

	sh->lex = lex;
	parser = NULL;
	tmp = sh->lex;
	parser = create_parser();
	parser->args = (char **)ft_calloc((count_words(tmp) + 1), sizeof(char *));
	process_tokens(sh, tmp, parser);
}
