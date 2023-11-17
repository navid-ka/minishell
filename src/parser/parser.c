/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 01:39:58 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/17 01:53:50 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *tok_type_changer(t_lexer *tmp)
{
    t_lexer *lex = tmp;
    int flag = 0;

    while (lex)
    {
        if (is_redir(lex->type))
        {
            if (lex->next && !flag)
            {
                lex->next->type = lex->type;
                flag = 1;
            }
            else if (lex->next && flag)
            {
                flag = 0;
            }
        }
        lex = lex->next;
    }

    return tmp;
}

void process_cmd_args(t_lexer *tmp, t_parser *parser)
{
	t_lexer *lex;
	int i = 0;

	lex = tmp;
	if (!parser->args)
		return;
	while (lex && lex->type != PIPE)
	{
		if (lex->type == CMD && !is_redir(lex->type))
		{
			parser->args[i] = ft_strdup(lex->str);
			i++;
		}
		lex = lex->next;
	}
	parser->args[i] = NULL;
	lex = tmp; 
}

void process_redirections(t_lexer *tmp, t_parser *parser)
{
    t_redir *new_redir;

    while (tmp && is_redir(tmp->type))
    {
        if (tmp->next != NULL && tmp->next->type != CMD)
        {
            new_redir = create_redir_node(tmp->next->str, tmp->type);
            //if (new_redir != NULL)
                redir_lstadd_back(&(parser->redir_list), new_redir);
            tmp = tmp->next->next;
            
            while (tmp && is_redir(tmp->type))
                tmp = tmp->next;
        }
        else
        {
            tmp = tmp->next;
        }
    }
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
	tmp = tok_type_changer(tmp);
	parser = create_parser();
	parser->args = (char **)ft_calloc((count_words(tmp) + 1), sizeof(char *));
	process_tokens(sh, tmp, parser);
}
