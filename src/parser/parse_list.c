/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:21:12 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/09 20:45:58 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*create_parser_node(char **args, t_redir red)
{
	t_parser *node;

	node = (t_parser *)malloc(sizeof(t_parser));
	node->args = args;
	node->red = red;
	node->next = NULL;
	return (node);
}

// void printparser_list(t_parser *parser_list)
// {
// 	t_parser *current = parser_list;
// 	// printf("primer comadno %s, segundo comando %s", parser_list->args[0], parser_list->next->args[0]);
// 	while (current != NULL) {
// 		// printf("Command: %s\n", current->args[0]);
// 		// printf("Arguments:\n");
// 		for (int i = 0; current->args != NULL && current->args[i] != NULL; i++)
// 		{
// 			printf("  %s\n", current->args[i]);
// 		}
// 		// printf("Redirection:\n");
// 		if (current->red.input != -1)
// 		{
// 			// printf("Input: %d\nInfile: %s\n", current->red.input, current->red.infile);
// 		}
// 		if (current->red.output != -1)
// 		{
// 			// printf("Output: %d\nOutfile: %s\n", current->red.output, current->red.outfile);
// 		}
// 		// printf("\n");
// 		current = current->next;
// 	}
// }