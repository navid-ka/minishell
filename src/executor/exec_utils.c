/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:52:20 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/10/18 15:52:24 by fcosta-f         ###   ########.fr       */
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