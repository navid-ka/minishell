/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:47:49 by bifrost           #+#    #+#             */
/*   Updated: 2023/10/15 00:18:47 by bifrost          ###   ########.fr       */
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
		args = NULL;
	}
}

void	clear_lexer(t_lexer **lexer_list)
{
	t_lexer	*middleman;
	t_lexer	*node;

	node = *lexer_list;
	while (node)
	{
		middleman = node->next;
		free(node->str);
		free(node);
		node = middleman;
	}
	*lexer_list = NULL;
}

void	clear_parser(t_parser **lst)
{
	t_parser	*middleman;
	t_parser	*node;
	int			i;

	i = 0;
	node = *lst;
	while (node)
	{
		middleman = node->next;
		free(node->args[i++]);
		free(node);
		node = middleman;
	}
	*lst = NULL;
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*tmp;

	current = *env;
	while (current != NULL)
	{
		tmp = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = tmp;
	}
	*env = NULL;
}