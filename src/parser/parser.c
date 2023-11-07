/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:16:14 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/11/07 12:52:16 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_words(t_lexer *tok)
{
	t_lexer	*first;
	int		words;

	first = tok;
	words = 0;
	while (first && first->type == CMD)
	{
		words++;
		first = first->next;
	}
	return (words);
}

// Function to handle command
void	handle_command(t_lexer **current_lexer, char ***args, int *idxarg)
{
	*args = (char **)ft_calloc((count_words(*current_lexer) + 1), \
			sizeof(char *));
	while (*current_lexer && (*current_lexer)->type == CMD)
	{
		(*args)[*idxarg] = ft_strdup((*current_lexer)->str);
		(*args)[*idxarg + 1] = NULL;
		(*idxarg)++;
		*current_lexer = (*current_lexer)->next;
	}
}

// Function to handle redirection
void	handle_redirection(t_lexer **current_lexer, t_redir *current_redir)
{
	if (*current_lexer && (*current_lexer)->type == INPUT)
	{
		*current_redir = create_redir_node(INPUT, 0, \
			(*current_lexer)->next->str, NULL);
		*current_lexer = (*current_lexer)->next->next;
	}
	else if (*current_lexer && (*current_lexer)->type == TRUNC)
	{
		*current_redir = create_redir_node(0, TRUNC, NULL, \
			(*current_lexer)->next->str);
		*current_lexer = (*current_lexer)->next->next;
	}
}

// Function to create new parser node
t_parser	*create_new_parser_node(t_parser **p_ls, t_parser **curr_p, \
	char **args, t_redir current_redir)
{
	t_parser	*new_parser_node;

	new_parser_node = create_parser_node(args, current_redir);
	if (*p_ls == NULL)
	{
		*p_ls = new_parser_node;
		*curr_p = *p_ls;
		(*p_ls)->num_cmds = 1;
	}
	else
	{
		(*curr_p)->next = new_parser_node;
		*curr_p = new_parser_node;
		(*p_ls)->num_cmds++;
	}
	return (new_parser_node);
}

// Function to convert the list of t_lexer into the list of t_parser
t_parser	*convert_lexer_parser(t_lexer *lexer, int idxarg)
{
	t_parser	*parser_ls;
	t_parser	*curr_parser;
	t_redir		curr_red;
	t_lexer		*curr_lex;
	char		**args;

	parser_ls = NULL;
	curr_parser = NULL;
	curr_lex = lexer;
	args = NULL;
	redir_init(&curr_red);
	while (curr_lex != NULL)
	{
		if (curr_lex->type == CMD)
		{
			handle_command(&curr_lex, &args, &idxarg);
			handle_redirection(&curr_lex, &curr_red);
			create_new_parser_node(&parser_ls, &curr_parser, args, curr_red);
			if (curr_lex)
				curr_parser->red.output = curr_lex->type;
		}
		else
			curr_lex = curr_lex->next;
	}
	return (parser_ls);
}
