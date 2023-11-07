/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:19:18 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/07 12:30:46 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    redir_init(t_redir *current_redir)
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
}
