/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:21:12 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/17 01:41:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser *create_parser(void)
{
	t_parser *parser;

	parser = ft_calloc(sizeof(t_parser), 1);
	parser->redir_list = NULL;
	parser->args = NULL;
	parser->next = NULL;
	return (parser);
}

t_parser	*parser_lstlast(t_parser *lst)
{
	t_parser	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node && node->next) // Add this check
		node = node->next;
	return (node);
}


void	parser_lstadd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (*lst)
	{
		last = parser_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_parser	*new_parser_node(char **args)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->args = args;
	node->next = NULL;
	return (node);
}


void printparser_list(t_mch *sh)
{
    t_parser *current = sh->parser;

    while (current) {
        int i = 0;
        while (current->args && current->args[i]) {
            printf("words: %s\n", current->args[i]);
            i++;
        }
        t_redir *redir = current->redir_list;
        if (redir) {
            while (redir) {
                printf("redirs: %s with type %d \n", redir->file, redir->type);
                redir = redir->next;
            }
        }
        current = current->next;
    }
}