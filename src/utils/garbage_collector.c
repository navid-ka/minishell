/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:47:49 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/17 21:46:30 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	clear_redir(t_redir **redir_list)
{
	t_redir	*middleman;
	t_redir	*node;

	node = *redir_list;
	while (node)
	{
		middleman = node->next;
		free(node->file);
		free(node);
		node = middleman;
	}
	*redir_list = NULL;
}

void	clear_parser(t_parser **lst)
{
	t_parser	*middleman;
	t_parser	*node;
	int			i;

	node = *lst;
	while (node)
	{
		middleman = node->next;
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		if (node->args != NULL)
		{
			free(node->args);
		}
		clear_redir(&node->redir_list);
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

void	unset_free(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
	env = NULL;
}
