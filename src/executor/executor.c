/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:19:59 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/06 22:25:59 by fcosta-f         ###   ########.fr       */
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

static void	open_infile(t_pipe *pipex, t_parser *pars)
{
	if (access(pars->red.infile, F_OK) == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, pars->red.infile));
	}
	// dprintf(2, "%s\n", pars->red.infile);
	pipex->fd_infile = open(pars->red.infile, O_RDONLY);
	pipex->permission = access(pars->red.infile, R_OK);
	dprintf(2, "%s, %d\n", pars->red.infile, pipex->fd_infile);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, pars->red.infile));
	}
	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	//close_pipes(pipex); //por qué si cierro pipe no funciona?
}

// static void	open_outfile(t_pipe *pipex, t_parser *pars)
// {
// 	pipex->fd_outfile = open(pars->red.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
// 	if (pipex->fd_outfile == -1)
// 	{
// 		close_pipes(pipex);
// 		exit(ft_error(1, ERR_NFD, pars->red.outfile));
// 	}
// 	pipex->permission = access(pars->red.outfile, W_OK);
// 	if (pipex->permission == -1)
// 	{
// 		close_pipes(pipex);
// 		exit(ft_error(1, ERR_PERM, pars->red.outfile));
// 	}
// 	dup2(pipex->fd_outfile, STDOUT_FILENO);
// 	close(pipex->fd_outfile);
// 	close_pipes(pipex);
// }

static void	child(t_pipe pipex, t_parser *pars, char **envp)
{
	if (pars->red.input == INPUT)
	{
		// dprintf(2, "hola\n");
		open_infile(&pipex, pars);
	}
	// if (pars->red.output == TRUNC)
	// 	open_outfile(&pipex, pars);
	// if (pars->red.input == PIPE)
	// 	dup2(pipex.tube[1], STDOUT_FILENO);
	// if (pars->red.output == PIPE)
	// 	dup2(pipex.tube[1], STDOUT_FILENO);
	// close_pipes(&pipex);

	char *args = find_cmd(envp, pars->args[0]);
	if (!pars->args[0])
		exit(127);
	// dprintf(2, "%s, %s\n", pars->args[0], pars->args[1]);
	execve(args, pars->args, envp); //creo que primero es ruta y segundo solo comando con args
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

int pipex(t_mch *all) 
{
	t_parser	*pars;
	t_pipe		*pipex;
	char		**routes;
	char		*path_env;
	int			status;

	pars = all->parser;
	pipex = all->pipex;
	pipex = ft_calloc(sizeof(t_pipe), 1);
	pipex->j = 2;
	path_env = get_path_env_value(all);
	routes = ft_split(path_env, ':');
	free(path_env);
	path_env = NULL;
	while (pars) {
		if (pars->next && pipe(pipex->tube))
			return (1);
		pipex->proc = fork();
		if (pipex->proc == 0)
			child(*pipex, pars, routes);
		else
		{
			int pid = waitpid(-1, &status, 0);
			if (pid == pipex->proc) all->exit = status;
			pars = pars->next;
		}
		if (WIFEXITED(all->exit))
			all->exit = WEXITSTATUS(all->exit);
	}
	free(pipex);
	free_tab(routes);
	return (all->exit);
}

void	executor(t_mch *sh)
{
	t_parser *cmd = sh->parser;
	
	if (!cmd || cmd->args[0] == NULL)
		return ;
	if (bt_is_builtin(cmd->args))
		bt_check_builtin(sh);
	else
		pipex(sh);
}