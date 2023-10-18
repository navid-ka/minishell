/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:19:59 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/18 16:08:07 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	open_infile(t_pipe *pipex, t_parser *pars)
{
	if (access(pars->red.infile, F_OK) == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, pars->red.infile));
	}
	pipex->fd_infile = open(pars->red.infile, O_RDONLY);
	pipex->permission = access(pars->red.infile, R_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, pars->red.infile));
	}
	dup2(pipex->fd_infile, STDIN_FILENO);
	close_pipes(pipex);
	close(pipex->fd_infile);
}

static void	open_outfile(t_pipe *pipex, t_parser *pars)
{
	pipex->fd_outfile = open(pars->red.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pipex->fd_outfile == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, pars->red.outfile));
	}
	pipex->permission = access(pars->red.outfile, W_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, pars->red.outfile));
	}
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close(pipex->fd_outfile);
	close_pipes(pipex);
}

static void	child(t_pipe pipex, t_parser *pars, char **envp)
{
	if (pars->red.input = INPUT)
		open_infile(&pipex, pars);
	if (pars->red.output = TRUNC)
		open_outfile(&pipex, pars);
	if (pars->red.input = PIPE)
		dup2(pipex.tube[1], STDOUT_FILENO);
	if (pars->red.output = PIPE)
		dup2(pipex.tube[1], STDOUT_FILENO);
	close_pipes(&pipex);
	pars->args[0] = find_cmd(envp, pars->args[0]);
	if (!pars->args[0])
		exit(127);
	execve(pars->args[0], pars->args, envp);
	exit (1);
}

void	last_pipe(t_pipe *pipex, int argc)
{
	if (pipex->j < argc - 2)
	{
		dup2(pipex->tube[0], STDIN_FILENO);
		close_pipes(pipex);
	}
}

int pipex(t_mch *all) {
	t_parser *pars;
	t_pipe *pipex;
	pars = all->parser;
	pipex = all->pipex;
	int exit_code;

	init_pipex(all->pipex, all->env);
	while (pars) {
		if (pars->next && pipe(pipex->tube))
			return (1);
		pipex->proc = fork();
		if (pipex->proc == 0)
			child(*pipex, pars, all->env);
		exit_code = wait_forks(&pipex);
		if (WIFEXITED(exit_code))
			exit(WEXITSTATUS(exit_code));
	}
	return (ft_error(1, ERR_ARG, NULL)); //no tiene que hacer exit creo
}

void	executor(t_mch *sh)
{
	t_parser *cmd = sh->parser;

	ft_printf(1,"EXECUTOR %s\n", cmd->args[0]);
	if (bt_is_builtin(cmd->args))
		bt_check_builtin(sh);
	else {
		dprintf(1, "entra pipex\n");
		pipex(sh);
	}
}