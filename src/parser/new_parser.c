/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/05 19:43:16 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//comando < archivo_de_entrada
//comando > archivo_de_salida
//comando >> archivo_de_salida
//comando << DELIMITADOR


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

static void init_parser(t_parser *parser)
{
    parser->args = NULL;
    parser->red = NULL;
    parser->next = NULL;
}
/*
static void init_redir(t_redir *redir)
{
    redir->input = 0;
    redir->output = 0;
    redir->infile = NULL;
    redir->outfile = NULL;
    redir->fd = 0;
    redir->next = NULL;
}*/

static void parse_cmd(t_lexer **lex, t_parser *parser)
{
    t_lexer *tmp = *lex; 
    int i = 0;

    parser->args = malloc(sizeof(char *) + 2); 
    while (tmp && tmp->type == CMD)
    {
        parser->args[i++] = ft_strdup(tmp->str);
        tmp = tmp->next;
    }

    //parser->args[i] = NULL;
    //parser->cmd = ft_strdup(parser->args[0]);
}
/*
static t_redir *parse_redirection(t_lexer **lex)
{
    t_redir *redir = malloc(sizeof(t_redir));
    if (redir == NULL)
    {
        ft_printf(2,"Error: Invalid output redirection format.\n");
        exit(1);  // Adjust the exit behavior as needed
    }
    init_redir(redir);

    if ((*lex)->type == INPUT)
    {
        redir->input = (*lex)->type;
        if ((*lex)->next && (*lex)->next->str) // Check if next node exists and has a string
        {
            redir->infile = ft_strdup((*lex)->next->str);
            *lex = (*lex)->next->next;
        }
        else
        {
            // Handle the case where there is no next node or no string
            ft_printf(2,"Error: Invalid output redirection format.\n");
            exit(1); // Or adjust the exit behavior as needed
        }
    }
    else if ((*lex)->type == TRUNC || (*lex)->type == APPEND)
    {
        redir->output = (*lex)->type;
        if ((*lex)->next && (*lex)->next->str) // Check if next node exists and has a string
        {
            redir->outfile = ft_strdup((*lex)->next->str);
            *lex = (*lex)->next->next;
        }
        else
        {
            // Handle the case where there is no next node or no string
            ft_printf(2,"Error: Invalid output redirection format.\n");
            exit(1); // Or adjust the exit behavior as needed
        }
    }

    return redir;
}

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

static void parse_pipe(t_lexer **lex, t_parser *parser)
{
    // Create a new redir structure for the pipe
    t_redir *redir = malloc(sizeof(t_redir));
    if (redir == NULL)
    {
        ft_printf(2, "Error: Memory allocation for pipe redirection failed.\n");
        exit(1); // Adjust the exit behavior as needed
    }
    init_redir(redir);

    // Set the output field in the redir structure
    redir->output = (*lex)->type;

    // Update the parser's redir field with the new redir structure
    append_redir(parser, redir);

    if (*lex)
    {
        (*lex) = (*lex)->next;
    }
}
*/
void parse_input(t_lexer *lex, t_parser *parser)
{
    t_lexer *tmp = lex;
    //t_redir *redir = NULL;

    while (tmp)
    {
        if (tmp->type == CMD)
        {
            parse_cmd(&tmp, parser);
        }
        /*else if (tmp->type == INPUT || tmp->type == TRUNC || tmp->type == APPEND)
        {
            redir = parse_redirection(&tmp);
            append_redir(parser, redir);
        }
        else if (tmp->type == PIPE)
            parse_pipe(&tmp, parser);*/

        tmp = tmp->next;
    }
    
   /* if (tmp && tmp->next)
    {
        parser->next = malloc(sizeof(t_parser));
        init_parser(parser->next);
        parser = parser->next;
    }*/
}

void parser(t_mch *sh, t_lexer *lex)
{
    int pipes = count_pipes(lex);
    sh->parser = malloc(sizeof(t_parser) * (pipes + 2));
    init_parser(sh->parser);
    parse_input(lex, sh->parser);
}