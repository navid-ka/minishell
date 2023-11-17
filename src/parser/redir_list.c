/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:19:18 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/17 21:40:25 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*void    redir_init(t_redir *current_redir)
{
    current_redir->infile = NULL;
	current_redir->outfile = NULL;
	current_redir->input = 0;
	current_redir->output = 0;
}
t_redir create_redir_node(int input, int output, char *infile, char *outfile)
{
	t_redir node;

	node.input = input;
	node.output = output;
	node.infile = ft_strdup(infile);
	node.outfile = ft_strdup(outfile);
	return (node);
}*/

t_redir	*redir_lstlast(t_redir *lst)
{
	t_redir	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node && node->next)
		node = node->next;
	return (node);
}

void	redir_lstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if ((*lst))
	{
		last = redir_lstlast(*lst);
		last->next = new;
	}
	else
		(*lst) = new;
}

t_redir	*create_redir_node(char *args, int type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->file = ft_strdup(args);
	node->type = type;
	node->next = NULL;
	return (node);
}
