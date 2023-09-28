/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/28 11:06:23 by nkeyani-         ###   ########.fr       */
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

static int	count_pipes(t_mch *sh, t_token *tok)
{
	int	pipes;

	pipes = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			pipes++;
		tok = tok->next;
	}
	sh->pipes = pipes;
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

static void cmd_init(t_cmd **cmd, int pipes)
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

static void	parse(t_token *tok, t_cmd **cmd)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (tok)
	{
		if (tok->type == WORD)
			argback(&(cmd[i]->arg), argnew(ft_strdup(tok->str)));
		else if (tok->type == REDIR)
		{
			redir = redir_type(tok);
			tok = tok->next;
			redirback(&(cmd[i]->red), redirnew(redir));
			argback(&(redirlast(cmd[i]->red)->arg),
				argnew(ft_strdup(tok->str)));
		}
		else
			i++;
		tok = tok->next;
	}
	i++;
	cmd[i] = NULL;
}

void	parser(t_mch *sh, t_token *tok)
{
	int	pipes;

	pipes = count_pipes(sh, tok);
	sh->cmd = malloc(sizeof (t_cmd *) * (pipes + 2));
	cmd_init(sh->cmd, pipes + 1);
	parse(tok, sh->cmd);
}

