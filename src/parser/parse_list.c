/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:21:12 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/10 19:24:01 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*t_parser	*create_parser_node(char **args, t_redir red)
{
	t_parser *node;

	node = (t_parser *)malloc(sizeof(t_parser));
	node->args = args;
	node->next = NULL;
	return (node);
}*/

void printparser_list(t_mch *sh)
{
	t_parser *current = sh->parser;
	t_redir *redir = sh->red;	
	while (current) {
		printf("command: ");
		int i = 0;
		while (current->args[i]) {
			printf("%s\n", current->args[i]);
			i++;
		}
		current = current->next;
	}
	printf("redirs: ");
	while (redir) {
		printf("%s with type %d\n", redir->file, redir->type);
		redir = redir->next;
	}
}