/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:51:16 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/09/05 19:56:26 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_infile(t_pipe *pipex, char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, argv[1]));
	}
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->permission = access(argv[1], R_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, argv[1]));
	}
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->tube[1], STDOUT_FILENO);
	close_pipes(pipex);
	close(pipex->infile);
}

static void	here_doc(t_pipe *pipex, char **argv)
{
	int		fd_doc[2];
	char	*str;

	pipex->limiter = argv[2];
	if (pipe(fd_doc) == -1)
		exit(1);
	if (ft_printf(1, ">") == -1)
		exit(1);
	str = get_next_line(0);
	while (str && ft_strncmp(str, pipex->limiter, ft_strlen(pipex->limiter)))
	{
		if (ft_printf(fd_doc[1], "%s", str) == -1)
			exit(1);
		free(str);
		if (ft_printf(1, ">") == -1)
			exit(1);
		str = get_next_line(0);
	}
	free(str);
	pipex->infile = fd_doc[0];
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->tube[1], STDOUT_FILENO);
	close(fd_doc[0]);
	close(fd_doc[1]);
}

static void	open_outfile(t_pipe *pipex, char *outfile)
{
	if (pipex->here_doc)
		pipex->outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		pipex->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pipex->outfile == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_NFD, outfile));
	}
	pipex->permission = access(outfile, W_OK);
	if (pipex->permission == -1)
	{
		close_pipes(pipex);
		exit(ft_error(1, ERR_PERM, outfile));
	}
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close_pipes(pipex);
}

static void	child(t_pipe pipex, char **argv, int argc, char **envp)
{
	if (pipex.j == 2 + pipex.here_doc)
	{
		if (pipex.here_doc)
			here_doc(&pipex, argv);
		else
			open_infile(&pipex, argv);
	}
	else if (pipex.j == argc - 2)
		open_outfile(&pipex, argv[argc - 1]);
	else
	{
		dup2(pipex.tube[1], STDOUT_FILENO);
		close_pipes(&pipex);
	}
	pipex.cmd_args = ft_split(argv[pipex.j], ' ');
	if (!pipex.cmd_args)
		return ;
	pipex.cmd = find_cmd(pipex.routes, pipex.cmd_args[0]);
	if (!pipex.cmd)
		exit(127);
	execve(pipex.cmd, pipex.cmd_args, envp);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		exit_code;

	if (argc >= 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc >= 6))
	{
		init_pipex(&pipex, argv, envp);
		while (pipex.j < argc - 1)
		{
			if (pipex.j < argc - 2 && pipe(pipex.tube))
				exit(1);
			pipex.proc = fork();
			if (pipex.proc == 0)
				child(pipex, argv, argc, envp);
			last_pipe(&pipex, argc);
			pipex.j++;
		}
		exit_code = wait_forks(&pipex);
		if (WIFEXITED(exit_code))
			exit(WEXITSTATUS(exit_code));
		exit(1);
	}
	return (ft_error(1, ERR_ARG, NULL));
}
