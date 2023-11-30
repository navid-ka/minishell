/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:34:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/30 14:35:41 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_infile(t_redir *top, t_pipe *pipex)
{
	if (access(top->file, F_OK) == -1)
	{
		close_pipes(pipex);
		ft_error(1, ERR_NFD, top->file);
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
}

void	open_outfile(t_redir *top, t_pipe *pipex)
{
	if (top->type == TRUNC)
		pipex->fd_outfile = open(top->file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		pipex->fd_outfile = open(top->file, O_WRONLY \
			| O_APPEND | O_CREAT, 0666);
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
}

void	open_redirs(t_pipe *pipex, t_redir *top)
{
	while (top)
	{
		if (top->type == INPUT)
			open_infile(top, pipex);
		else if (top->type == HERE_DOC)
			manage_here_doc(top, pipex->proc);
		else if (top->type == TRUNC || top->type == APPEND)
			open_outfile(top, pipex);
		top = top->next;
	}
}

void	init_redirs(t_pipe *pipex)
{
	pipex->std_in = dup(STDIN_FILENO);
	pipex->std_out = dup(STDOUT_FILENO);
}

void	reset_redirs(t_pipe *pipex)
{
	dup2(pipex->std_in, STDIN_FILENO);
	dup2(pipex->std_out, STDOUT_FILENO);
}
