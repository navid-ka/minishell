/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_javi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:16:14 by fcosta-f          #+#    #+#             */

/*   Updated: 2023/10/18 16:07:00 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// t_parser parser(t_lexer lex) {
	
// }

// Función para crear un nuevo nodo de t_parser
t_parser *create_parser_node(char **args, t_redir red)
{
    t_parser *node = (t_parser *)malloc(sizeof(t_parser));
    node->args = args;
    node->red = red;
    node->next = NULL;
    return node;
}

// Función para crear un nuevo nodo de t_redir
t_redir create_redir_node(int input, int output, char *infile, char *outfile)
{
    t_redir node;
    node.input = input;
    node.output = output;
    node.infile = ft_strdup(infile);
    node.outfile = ft_strdup(outfile);
    return (node);
}

int count_words(t_lexer *tok) 
{
	t_lexer *first = tok;
	int words = 0;
	while (first && first->type == CMD)
	{
		words++;
		first = first->next;
	}
	return (words);
}

// Función para convertir la lista de t_lexer en la lista de t_parser
t_parser *convert_lexer_parser(t_lexer *lexerList)
{
    t_parser *parser_list = NULL;
    t_parser *current_parser = NULL;
    t_redir current_redir;
    t_lexer *current_lexer = lexerList;
    while (current_lexer != NULL) {
        if (current_lexer->type == CMD)
		{
            char **args = NULL;
            if ((current_lexer->next != NULL \
                && (current_lexer->next->type != INPUT || current_lexer->next->type != TRUNC)) \
                || current_lexer->next == NULL) /*ORAPPEND*/
            {

				int idxarg = 0;

				args = (char **)ft_calloc((count_words(current_lexer) + 1), sizeof(char *));
                while (current_lexer && current_lexer->type == CMD)
				{
                    // Agregar argumento a args
                    args[idxarg] = ft_strdup(current_lexer->str);
                    args[idxarg + 1] = NULL;
					idxarg++;
					current_lexer = current_lexer->next;
                }
				current_redir.infile = NULL;
				current_redir.outfile = NULL;
				current_redir.input = 0;
				current_redir.output = 0;
				if (current_lexer && current_lexer->type == INPUT)
				{
                    // Iniciar redirección de entrada
					//posiblemente crear type output para ir viendo si siguiente es NULL o hay pipe o similar; en output similar para obtener la entrada
                    current_redir = create_redir_node(INPUT, 0, current_lexer->next->str, NULL);
                    current_lexer = current_lexer->next->next; // Saltar el nombre del archivo de entrada
                } else if (current_lexer && current_lexer->type == TRUNC) {
                    // Iniciar redirección de salida
                    current_redir = create_redir_node(0, TRUNC, NULL, current_lexer->next->str);
                    current_lexer = current_lexer->next->next; // Saltar el nombre del archivo de salida
                }
                //current_lexer = current_lexer->next;
            }
            t_parser *new_parser_node = create_parser_node(args, current_redir);
            if (parser_list == NULL) {
                parser_list = new_parser_node;
                current_parser = parser_list;
				        parser_list->num_cmds = 1;
            }
			else {
                current_parser->next = new_parser_node;
                current_parser = new_parser_node;
				parser_list->num_cmds++;
				// if (current_lexer->prev && current_lexer->prev->prev != NULL) current_parser->red.input = current_lexer->prev->type;
            }
			if (current_lexer) 
                current_parser->red.output = current_lexer->type;
        } 
		else {
            current_lexer = current_lexer->next;
        }

    }
    return (parser_list);
}

// Función para imprimir la lista de t_parser (para fines de depuración)
void printparser_list(t_parser *parser_list)
{
    t_parser *current = parser_list;
	// printf("primer comadno %s, segundo comando %s", parser_list->args[0], parser_list->next->args[0]);
    while (current != NULL) {
        // printf("Command: %s\n", current->args[0]);
        // printf("Arguments:\n");
        for (int i = 0; current->args != NULL && current->args[i] != NULL; i++)
		{
            printf("  %s\n", current->args[i]);
        }
        // printf("Redirection:\n");
		if (current->red.input != -1)
		{
			// printf("Input: %d\nInfile: %s\n", current->red.input, current->red.infile);
		}
		if (current->red.output != -1)
		{
			// printf("Output: %d\nOutfile: %s\n", current->red.output, current->red.outfile);
		}
        // printf("\n");
        current = current->next;
    }
}