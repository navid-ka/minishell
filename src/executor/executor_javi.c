/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_javi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:20:57 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/11/18 01:21:07 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_path_env_value(t_mch *sh)
{
	char	*path_env_value;

	path_env_value = get_env_value(sh, "PATH");
	if (path_env_value == NULL)
	{
		sh->exit = 1;
		ft_printf(2, "No such file or directory\n");
		return (NULL);
	}
	sh->exit = 0;
	return (path_env_value);
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
 //cosas antiguas arriba

void open_infile(t_redir *top, t_pipe *pipex) {

	if (access(top->file, F_OK) == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, top->file));
	}
	pipex->fd_infile = open(top->file, O_RDONLY);
	pipex->permission = access(top->file, R_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, top->file));
	}
	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	close_pipes(pipex); //por qué si cierro pipe no funciona?
}

void open_outfile(t_redir *top, t_pipe *pipex) {
	
	pipex->fd_outfile = open(top->file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pipex->fd_outfile == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, top->file));
	}
	pipex->permission = access(top->file, W_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, top->file));
	}
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close(pipex->fd_outfile);
	// if (pars->next)
	// 	close_pipes(pipex); oh mama
}

void 	open_redirs(t_pipe *pipex, t_redir *top) {
	
	while (top)
	{
		if (top->type == INPUT) {
			open_infile(top, pipex);
		}
		if (top->type == TRUNC) {
			open_outfile(top, pipex);
		}
		top = top->next;
	}
}

void child(t_parser *top, t_pipe *ptop, int first, char **routes) {
	t_parser *pars;
	t_pipe *pipex;

	pars = top;
	pipex = ptop;
	
	if (!first) {
		dup2(pipex->tube[0], STDIN_FILENO);
	}
	if (pars->next) {
		dup2(pipex->tube[1], STDOUT_FILENO);
	}
	if (ptop->npipes > 1) close_pipes(pipex);
	char *args = find_cmd(routes, pars->args[0]);
	if (!pars->args[0])
		exit(127);
	execve(args, pars->args, routes); //creo que primero es ruta y segundo solo comando con args
	exit (1);
}

int executor(t_mch *all) {
	t_parser *pars;
	t_pipe *pipex;
	int first;
	char *path_env;
	char **routes;
	
	pipex = all->pipex;
	pars = all->parser;
	first = 1;
	pipex = ft_calloc(sizeof(t_pipe), 1);
	path_env = get_path_env_value(all);
	routes = ft_split(path_env, ':');
	free(path_env);
	path_env = NULL;
	while (pars) {
		if (pars->next && pipe(pipex->tube))
			return (1);
		pipex->proc = fork();
		if (pipex->proc == 0) {
			open_redirs(pipex, pars->redir_list);
			child(pars, pipex, first, routes);
		}
		// close_pipes(pipex);
		waitpid(pipex->proc, NULL, 0);
		first = 0;
		pars = pars->next;
	}
	return(0);
}