/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/05 15:02:57 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//comando < archivo_de_entrada
//comando > archivo_de_salida
//comando >> archivo_de_salida
//comando << DELIMITADOR

// Function to count pipes in the lexer
static int count_pipes(t_lexer *lexer)
{
    int pipes = 0;
    t_lexer *lex = lexer;

    while (lex)
    {
        if (lex->type == PIPE)
            pipes++;
        lex = lex->next;
    }

    return pipes;
}

// Function to initialize a t_parser structure
static void init_parser(t_parser *parser)
{
    parser->cmd = NULL;
    parser->args = NULL;
    parser->red = NULL;
    parser->next = NULL;
}

// Function to initialize a t_redir structure
static void init_redir(t_redir *redir)
{
    redir->input = 0;
    redir->output = 0;
    redir->infile = NULL;
    redir->outfile = NULL;
    redir->fd = 0;
    redir->next = NULL;
}

// Function to parse a command and populate a t_parser structure
static void parse_cmd(t_lexer **lex, t_parser *parser)
{
    int i = 0;
    while (*lex && (*lex)->type == CMD)
    {
        parser->args = realloc(parser->args, (i + 2) * sizeof(char *));
        parser->args[i++] = ft_strdup((*lex)->str);
        *lex = (*lex)->next;
    }
    parser->args[i] = NULL;
    parser->cmd = ft_strdup(parser->args[0]);
}

// Function to parse redirection and create a t_redir structure
static t_redir *parse_redirection(t_lexer **lex)
{
    t_redir *redir = malloc(sizeof(t_redir));
    init_redir(redir);

    if ((*lex)->type == INPUT)
    {
        redir->input = (*lex)->type;
        redir->infile = ft_strdup((*lex)->next->str);
        *lex = (*lex)->next->next;
    }
    else if ((*lex)->type == TRUNC || (*lex)->type == APPEND)
    {
        redir->output = (*lex)->type;
        redir->outfile = ft_strdup((*lex)->next->str);
        *lex = (*lex)->next->next;
    }

    return redir;
}

// Function to append a t_redir structure to the linked list of redirections
static void append_redir(t_parser *parser, t_redir *redir)
{
    if (parser->red == NULL)
    {
        parser->red = redir;
    }
    else
    {
        t_redir *current = parser->red;
        while (current->next)
        {
            current = current->next;
        }
        current->next = redir;
    }
}

// Function to handle pipe logic
static void parse_pipe(t_lexer **lex)
{
    // Handle pipe logic here
    if (*lex)
    {
        (*lex) = (*lex)->next;
    }
}

// Function to handle the overall parsing loop and creation of t_parser structures
// Function to handle the overall parsing loop and creation of t_parser structures
void parse_input(t_lexer *lex, t_parser *parser)
{
    t_lexer *tmp = lex;

    while (tmp)
    {
        if (tmp->type == CMD)
        {
            parse_cmd(&tmp, parser);
        }
        else if (tmp->type == INPUT || tmp->type == TRUNC || tmp->type == APPEND)
        {
            t_redir *redir = parse_redirection(&tmp);
            append_redir(parser, redir);
        }
        else if (tmp->type == PIPE)
        {
            parse_pipe(&tmp);  // Remove the 'parser' argument here
        }

        tmp = tmp->next;

        if (tmp)
        {
            parser->next = malloc(sizeof(t_parser));
            init_parser(parser->next);
            parser = parser->next;
        }
    }
}

// Function to initiate the parsing process
void parser(t_mch *sh, t_lexer *lex)
{
    int pipes = count_pipes(lex);
    sh->parser = malloc(sizeof(t_parser) * (pipes + 1));
    init_parser(sh->parser);
    parse_input(lex, sh->parser);
}