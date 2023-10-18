
// #include "../../inc/minishell.h"

// t_redir	*redirnew(int type)
// {
// 	t_redir	*node;

// 	node = (t_redir *)malloc(sizeof (*node));
// 	if (!node)
// 		return (NULL);
// 	node->arg = NULL;
// 	node->type = type;
// 	node->next = NULL;
// 	return (node);
// }

// void	redirback(t_redir **lst, t_redir *new)
// {
// 	t_redir	*curr;

// 	if (!lst || !new)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	curr = redirlast(*lst);
// 	curr->next = new;
// }

// t_redir	*redirlast(t_redir *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst != NULL)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }
