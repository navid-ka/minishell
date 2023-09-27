#include "../../inc/minishell.h"

t_arg	*argnew(void *content)
{
	t_arg	*node;

	node = (t_arg *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->arg = content;
	node->next = NULL;
	return (node);
}

void	argback(t_arg **lst, t_arg *new)
{
	t_arg	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = arglast(*lst);
	curr->next = new;
}

t_arg	*arglast(t_arg *lst)
{
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	argsize(t_arg *lst)
{
	int	c;

	c = 0;
	while (lst != NULL)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}

void	argfront(t_arg **lst, t_arg *new)
{
	if (lst)
	{
		if (!lst || !new)
			return ;
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			new->next = *lst;
			*lst = new;
		}
	}
}
