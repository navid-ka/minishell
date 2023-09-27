/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/27 17:42:22 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	categorizer(t_token *tok)
{
	while (tok)
	{
		if (ft_strcmp(tok->tok, "|") == 0)
			tok->type = "PIPE";
		else if (ft_strcmp(tok->tok, ">") == 0
			|| ft_strcmp(tok->tok, "<") == 0
			|| ft_strcmp(tok->tok, ">>") == 0
			|| ft_strcmp(tok->tok, "<<") == 0)
			tok->type = "REDIR";
		else
			tok->type = "WORD";
		tok = tok->next;
	}
}

static int	pipes(t_cmd *arg, t_token *tok)
{
	int	pipes;

	pipes = 0;
	while (tok)
	{
		if (tok->type == "PIPE")
			pipes++;
		tok = tok->next;
	}
	return (pipes);
}

static int	redir_type(t_token *tok)
{
	if (ft_strcmp(tok->str, "<") == 0)
		return (TRUNC);
	if (ft_strcmp(tok->str, ">") == 0)
		return (INPUT);
	if (ft_strcmp(tok->str, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(tok->str, "<<") == 0)
		return (HERE_DOC);
	return (-1);
}

// NECESITAMOS CAMBIAR A STR EL TYPE PARA HACERLO MAS FACIL