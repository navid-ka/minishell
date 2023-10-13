/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:19:59 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/13 17:11:00 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_error(int ext, int err, char *cmd)
{
	if (err == ERR_ARG)
		ft_printf(2, "bash: Invalid number of arguments\n");
	else if (err == ERR_MC)
		ft_printf(2, "bash: error trying to allocate memory\n");
	else if (err == ERR_CNF)
		ft_printf(2, "bash: %s: command not found\n", cmd);
	else if (err == ERR_NFD)
		ft_printf(2, "bash: %s: No such file or directory\n");
	else if (err == ERR_PERM)
		ft_printf(2, "bash: %s: permission denied\n");
	else if (err == ERR_PERR)
		perror("bash: ");
	return (ext);
}

char	*find_path(char **envp, int *found)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		*found = 0;
		return (NULL);
	}
	*found = 1;
	return (envp[i] + 5);
}

int	find_route(t_pipe *pipex, char **envp)
{
	int	found;

	pipex->routes = ft_split(find_path(envp, &found), ':');
	if (!found)
		return (1);
	if (!pipex->routes)
		return (ft_error(1, ERR_MC, NULL));
	return (0);
}

void	init_pipex(t_pipe *pipex, char **envp)
{
	if (find_route(pipex, envp) == 1)
		exit(1);
	pipex->j = 2; /*+ pipex->here_doc;*/
	//heredoc?
}

void	close_pipes(t_pipe *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

char	*find_cmd(char **routes, char *cmd)
{
	char	*tmp;
	char	*cmdroute;

	while (*routes)
	{
		tmp = ft_strjoin(*routes, "/");
		cmdroute = ft_strjoin(tmp, cmd);
		if (!cmdroute)
		{
			ft_error(1, ERR_MC, NULL);
			return (NULL);
		}
		free(tmp);
		if (access(cmdroute, F_OK | X_OK) == 0)
			return (cmdroute);
		free(cmdroute);
		++routes;
	}
	if (access(cmd, F_OK | X_OK) == 0 && ft_strchr(cmd, '/'))
		return (cmd);
	else
		ft_error(127, ERR_CNF, cmd);
	return (NULL);
}

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
	dup2(pipex->tube[1], STDOUT_FILENO);
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
	if (pipex.j == 2)
		open_infile(&pipex, pars);
	else if (pipex.j == pars->num_cmds - 1)
		open_outfile(&pipex, pars);
	else
	{
		dup2(pipex.tube[1], STDOUT_FILENO);
		close_pipes(&pipex);
	}
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

int	wait_forks(t_pipe *pipex)
{
	int	status;
	int	exit_code;

	while (pipex->j > 2 + pipex->here_doc)
	{
		if (wait(&status) == pipex->proc)
			exit_code = status;
		pipex->j--;
	}
	return (exit_code);
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
		pipex(sh);
	}
}