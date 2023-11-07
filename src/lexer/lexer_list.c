/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:20:17 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/07 10:20:42 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*lexer_lstnew(void)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = NULL;
	node->type = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_lexer	*lexer_lstlast(t_lexer *lst)
{
	t_lexer	*node;

	if (!lst)
		return (0);
	node = lst;
	while ((node->next))
		node = node->next;
	return (node);
}

void	lexer_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if ((*lst))
	{
		last = lexer_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		(*lst) = new;
}

void	lexer_lstclear(t_lexer **lst)
{
	t_lexer	*nxt;
	t_lexer	*aux;

	aux = *lst;
	while (aux)
	{
		nxt = aux->next;
		free(aux->str);
		free(aux);
		aux = nxt;
	}
	*lst = NULL;
}

int	lexer_lstsize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
