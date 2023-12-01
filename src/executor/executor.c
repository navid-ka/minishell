/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:19:59 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/01 14:54:39 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_pipe(t_mch *all, t_parser *pars, t_pipe *pipex)
{
	pipe(pipex->tube);
	pipex->proc = fork();
	if (pipex->proc == 0)
	{
		open_redirs(pipex, pars->redir_list);
		if (all->pipes > 1)
		{
			child_pipes(pars, pipex, all);
			dup2(pipex->tube[0], STDIN_FILENO);
		}
		else
			child(pars, pipex, all);
	}
	else
		pars = pars->next;
	dup2(pipex->tube[0], 0);
	close_pipes(pipex);
}

int	execute(t_mch *all)
{
	t_parser	*pars;
	t_pipe		*pipex;

	pipex = all->pipex;
	pars = all->parser;
	pipex = ft_calloc(sizeof(t_pipe), 1);
	init_redirs(pipex);
	if (!pipex)
		return (ft_error(1, ERR_MC, NULL));
	load_routes(pipex, all);
	while (pars)
	{
		execute_pipe(all, pars, pipex);
		pars = pars->next;
	}
	reset_redirs(pipex);
	all->exit = wait_childs(pipex, all);
	exec_free(pipex);
	return (all->exit);
}

int	executor(t_mch *all)
{
	if (bt_is_builtin(all->parser->args) && all->pipes == 1)
	{
		if (all->parser->redir_list)
			execute(all);
		else
			exec_bt(all, all->parser);
	}
	else
		all->exit = execute(all);
	return (all->exit);
}
