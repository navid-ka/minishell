/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:19:59 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/01 14:50:38 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_parser *top, t_pipe *pipex, t_mch *all)
{
	t_parser	*pars;

	pars = top;
	if (bt_is_builtin(pars->args))
	{
		exec_bt(all, pars);
		exit(1);
	}
	else
	{
		pipex->file_path = get_args(pars, pipex->routes);
		execve(pipex->file_path, pars->args, pipex->routes);
		exit(1);
	}
}

void	child_pipes(t_parser *top, t_pipe *ptop, t_mch *all)
{
	t_pipe		*pipex;
	t_parser	*pars;

	pipex = ptop;
	pars = top;
	close(pipex->tube[0]);
	if (pars->next)
	{
		dup2(pipex->tube[1], STDOUT_FILENO);
		close(pipex->tube[1]);
	}
	else
		close(pipex->tube[1]);
	if (bt_is_builtin(pars->args))
	{
		exec_bt(all, pars);
		exit(all->exit);
	}
	else
	{
		pipex->file_path = get_args(pars, pipex->routes);
		execve(pipex->file_path, pars->args, pipex->routes);
		exit(all->exit);
	}
}

int	wait_childs(t_pipe *pipe, t_mch *all)
{
	int		i;
	int		status;
	pid_t	pid;
	int		real_status;

	i = -1;
	while (++i < all->pipes)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pipe->proc)
			real_status = status;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			real_status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf(3, "Quit: 3\n");
			real_status = 131;
		}
	}
	return (real_status);
}
