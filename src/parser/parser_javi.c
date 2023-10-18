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
t_parser *createParserNode(char **args, t_redir red) {
    t_parser *node = (t_parser *)malloc(sizeof(t_parser));
    node->args = args;
    node->red = red;
    node->next = NULL;
    return node;
}

// Función para crear un nuevo nodo de t_redir
t_redir createRedirNode(int input, int output, char *infile, char *outfile) {
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
t_parser *convertLexerToParser(t_lexer *lexerList) {
    t_parser *parserList = NULL;
    t_parser *currentParser = NULL;
    t_redir currentRedir;
    t_lexer *currentLexer = lexerList;
    while (currentLexer != NULL) {
        if (currentLexer->type == CMD) {
            char **args = NULL;
            if ((currentLexer->next != NULL \
                && (currentLexer->next->type != INPUT || currentLexer->next->type != TRUNC)) \
                || currentLexer->next == NULL) /*ORAPPEND*/
            {

				int argCount = 0;

				args = (char **)ft_calloc((count_words(currentLexer) + 1), sizeof(char *));
                while (currentLexer && currentLexer->type == CMD) {
                    // Agregar argumento a args
                    args[argCount] = ft_strdup(currentLexer->str);
                    args[argCount + 1] = NULL;
					argCount++;
					currentLexer = currentLexer->next;
                }
				currentRedir.infile = NULL;
				currentRedir.outfile = NULL;
				currentRedir.input = 0;
				currentRedir.output = 0;
				if (currentLexer && currentLexer->type == INPUT) {
                    // Iniciar redirección de entrada
					//posiblemente crear type output para ir viendo si siguiente es NULL o hay pipe o similar; en output similar para obtener la entrada
                    currentRedir = createRedirNode(INPUT, 0, currentLexer->next->str, NULL);
                    currentLexer = currentLexer->next->next; // Saltar el nombre del archivo de entrada
                } else if (currentLexer && currentLexer->type == TRUNC) {
                    // Iniciar redirección de salida
                    currentRedir = createRedirNode(0, TRUNC, NULL, currentLexer->next->str);
                    currentLexer = currentLexer->next->next; // Saltar el nombre del archivo de salida
                }
                //currentLexer = currentLexer->next;
            }
            t_parser *newParserNode = createParserNode(args, currentRedir);
            if (parserList == NULL) {
                parserList = newParserNode;
                currentParser = parserList;
				        parserList->num_cmds = 1;
            }
			else {
                currentParser->next = newParserNode;
                currentParser = newParserNode;
				parserList->num_cmds++;
				// if (currentLexer->prev && currentLexer->prev->prev != NULL) currentParser->red.input = currentLexer->prev->type;
            }
			if (currentLexer) currentParser->red.output = currentLexer->type;
        } 
		else {
            currentLexer = currentLexer->next;
        }
    }
    return (parserList);
}

// Función para imprimir la lista de t_parser (para fines de depuración)
void printParserList(t_parser *parserList) {
    t_parser *current = parserList;
	// printf("primer comadno %s, segundo comando %s", parserList->args[0], parserList->next->args[0]);
    while (current != NULL) {
        // printf("Command: %s\n", current->args[0]);
        // printf("Arguments:\n");
        for (int i = 0; current->args != NULL && current->args[i] != NULL; i++) {
            printf("  %s\n", current->args[i]);
        }
        // printf("Redirection:\n");
		if (current->red.input != -1) {
			// printf("Input: %d\nInfile: %s\n", current->red.input, current->red.infile);
		}
		if (current->red.output != -1) {
			// printf("Output: %d\nOutfile: %s\n", current->red.output, current->red.outfile);
		}
        // printf("\n");
        current = current->next;
    }
}