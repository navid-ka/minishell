/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:16:14 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/11/17 01:40:39 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(int type)
{
	if (type == TRUNC || type == APPEND \
		|| type == HERE_DOC || type == INPUT)
		return (1);
	return (0);
}

int count_pipes(t_lexer *lex)
{
	int n;
	t_lexer *tmp;

	tmp = lex;
	n  = 1;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		tmp = tmp->next;
	} 
	return (n);
}

int	count_words(t_lexer *tok)
{
	t_lexer	*first;
	int		words;

	first = tok;
	words = 0;
	while (first)
	{
		words++;
		first = first->next;
	}
	return (words);
}