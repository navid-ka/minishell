/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:47:49 by bifrost           #+#    #+#             */
/*   Updated: 2023/10/14 18:52:51 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	free_tab(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	clear_lexer(t_lexer **lexer_list)
{
	t_lexer	*current;

	current = *lexer_list;
	if (lexer_list == NULL || current == NULL)
		return ;
	if (lexer_list)
	{
		while (current->next != NULL)
		{
			current = (*lexer_list)->next;
			free((*lexer_list)->str);
			(*lexer_list)->str = NULL;
			free(*lexer_list);
			*lexer_list = current;
		}
		free((*lexer_list)->str);
		(*lexer_list)->str = NULL;
		free(*lexer_list);
	}
    *lexer_list = NULL;
}

void	clear_parser(t_parser **lst)
{
	t_parser	*middleman;
	t_parser	*node;

	node = *lst;
	while (node)
	{
		middleman = node->next;
		free_tab(node->args);
		node = middleman;
	}
}
