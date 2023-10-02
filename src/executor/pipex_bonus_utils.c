/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:57:04 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/10/01 13:11:21 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_pipex(t_pipe *pipex, char **argv, char **envp)
{
	if (find_route(pipex, envp) == 1)
		exit(1);
	pipex->here_doc = !ft_strncmp(argv[1], "here_doc", 9);
	pipex->j = 2 + pipex->here_doc;
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

void	close_pipes(t_pipe *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}
