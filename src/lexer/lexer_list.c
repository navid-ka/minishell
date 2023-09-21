#include "../../inc/minishell.h"

t_token	*lexer_lstnew(void)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = NULL;
	node->type = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_token	*lexer_lstlast(t_token *lst)
{
	t_token	*node;

	if (!lst)
		return (0);
	node = lst;
	while ((node->next))
		node = node->next;
	return (node);
}

void	lexer_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if ((*lst))
	{
		last = lexer_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		(*lst) = new;
	// printf("new: %s, %d\n uwu: %s, %d", new->str, new->type, last->next->str, last->next->type);
}

void	lexer_lstclear(t_token **lst)
{
	t_token	*nxt;
	t_token	*aux;

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

int	lexer_lstsize(t_token *lst)
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
