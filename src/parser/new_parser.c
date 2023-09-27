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

void	symbol_sorter(t_token *tok)
{
	while (tok)
	{
		if (ft_strcmp(tok->str, "|") == 0)
			tok->type = PIPE;
		else if (ft_strcmp(tok->str, ">") == 0
			|| ft_strcmp(tok->str, "<") == 0
			|| ft_strcmp(tok->str, ">>") == 0
			|| ft_strcmp(tok->str, "<<") == 0)
			tok->type = REDIR;
		else
			tok->type = WORD;
		tok = tok->next;
	}
}

static int	pipes(t_cmd *arg, t_token *tok)
{
	int	pipes;

	pipes = 0;
	while (tok)
	{
		if (tok->type == PIPE)
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

static	void cmd_init(t_cmd **cmd, int pipes)
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		cmd[i] = malloc(sizeof (t_cmd));
		cmd[i]->red = NULL;
		cmd[i]->red_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->arg_x = NULL;
		cmd[i]->args = NULL;
		i++;
	}
	cmd[i] = NULL;
}

static void	parse(t_tok *tok, t_cmd **cmd)
{
	int	j;
	int	redir;

	i = 0;
	redir = 0;
	while (tok)
	{
		if (tok->type == WORD)
			argback(&(cmd[j]->arg), argnew(ft_strdup(tok->tok)));
		else if (tok->type == REDIR)
		{
			redir = redir_type(tok);
			tok = tok->next;
			redirback(&(cmd[j]->red), redirnew(redir));
			argback(&(redirlast(cmd[j]->red)->arg),
				argnew(ft_strdup(tok->tok)));
		}
		else
			i++;
		tok = tok->next;
	}
	i++;
	cmd[j] = NULL;
}

void	parser(t_mch *sh)
{
	int	pipes;

	pipes = count_pipes(sh, sh->tok);
	sh->s_cmd = malloc(sizeof (t_cmd *) * (pipes + 2));
	init(sh->s_cmd, pipes + 1);
	parse(sh->tok, sh->s_cmd);
}

// NECESITAMOS CAMBIAR A STR EL TYPE PARA HACERLO MAS FACIL
