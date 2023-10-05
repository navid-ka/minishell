//#include "../../inc/minishell.h"

// t_parser	*parse_new(char **content)
// {
// 	t_parser	*node;

// 	node = (t_parser *)malloc(sizeof (*node));
// 	if (!node)
// 		return (NULL);
// 	node->args = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	parse_back(t_parser **lst, t_parser *new)
// {
// 	t_parser	*curr;

// 	if (!lst || !new)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	curr = parse_last(*lst);
// 	curr->next = new;
// }

// t_parser	*parse_last(t_parser *lst)
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

// int	parse_size(t_parser *lst)
// {
// 	int	c;

// 	c = 0;
// 	while (lst != NULL)
// 	{
// 		c++;
// 		lst = lst->next;
// 	}
// 	return (c);
// }

// void	parse_front(t_parser **lst, t_parser *new)
// {
// 	if (lst)
// 	{
// 		if (!lst || !new)
// 			return ;
// 		if (*lst == NULL)
// 		{
// 			*lst = new;
// 			new->next = NULL;
// 		}
// 		else
// 		{
// 			new->next = *lst;
// 			*lst = new;
// 		}
// 	}
// }