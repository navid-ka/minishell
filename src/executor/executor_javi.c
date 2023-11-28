/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_javi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:20:57 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/11/28 23:18:58 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

int is_fd_open(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
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
	sh->exit = 0; //esto se conserva?
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
		ft_error(127, ERR_CNF, cmd); //este exit_code dónde queda?
	return (NULL);
}
 //cosas antiguas arriba

void open_infile(t_redir *top, t_pipe *pipex)
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
	//close_pipes(pipex); //por qué si cierro pipe no funciona?
}

void open_outfile(t_redir *top, t_pipe *pipex)
{
	if (top->type == TRUNC) {
		pipex->fd_outfile = open(top->file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	else
		pipex->fd_outfile = open(top->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
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

void 	open_redirs(t_pipe *pipex, t_redir *top)
{
	while (top)
	{
		if (top->type == INPUT) {
			open_infile(top, pipex);
		}
		else if (top->type == HERE_DOC)
		{
			manage_here_doc(top, pipex->proc);
		}
		else if (top->type == TRUNC|| top->type == APPEND) {
			open_outfile(top, pipex);
		}
		/*else if (top->type == PIPE) {
			dup2(pipex->tube[1], 1);
			dup2(pipex->tube[0], 0);
			break;
		}*/
		top = top->next;
	}
}

void child(t_parser *top, t_pipe *ptop, int first, char **routes, t_mch *all) {
    t_parser *pars;
    t_pipe *pipex;

    pars = top;
    pipex = ptop;
    
    if (!first) {
        dup2(pipex->tube[0], STDIN_FILENO);
        close(pipex->tube[0]);
    }
    if (pars->next) {
        dup2(pipex->tube[1], STDOUT_FILENO);
        close(pipex->tube[1]);
    }
	close(pipex->tube[0]);
    close(pipex->tube[1]);
    if (bt_is_builtin(pars->args)) {
        bt_check_builtin(all);
        exit(1);
    }
    char *args = find_cmd(routes, pars->args[0]);
    if (!pars->args[0])
        exit(127);
    execve(args, pars->args, routes);
    exit (1);
}

int	wait_childs(t_pipe *pipe, t_mch *all/*, int *exit_s*/)
{
	int	i;
	int	status;
	pid_t pid;
	int real_status;

	i = 0;
	// dprintf(2, "%d", all->pipes);
	while (i < all->pipes + 1)
	{
		pid = waitpid(-1, &status, 0);
		i++;
		if (pid == pipe->proc) real_status = status;
	}
	// dup2(pipe->std_in, STDIN_FILENO);
	// dup2(pipe->std_out, STDOUT_FILENO);
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

int executor(t_mch *all) {
    t_parser *pars;
    t_pipe *pipex;
    int first;
    char *path_env;
    char **routes;
    int fd_in = 0;  // Entrada inicial para el primer comando

    pipex = all->pipex;
    pars = all->parser;
    first = 1;
    pipex = ft_calloc(sizeof(t_pipe), 1);
    if ((path_env = get_path_env_value(all)) == NULL)
        return (127);
    routes = ft_split(path_env, ':');
    free(path_env);
    path_env = NULL;
    while (pars) {
        pipe(pipex->tube);  // Crear un pipe
        pipex->proc = fork();
        if (pipex->proc == 0) {
            if (!first) {  // Si no es el primer comando
                dup2(fd_in, STDIN_FILENO);  // Usar la entrada del pipe anterior
            }
            if (pars->next) {  // Si no es el último comando
                dup2(pipex->tube[1], STDOUT_FILENO);  // Usar la salida del pipe actual
            }
            close(pipex->tube[0]);  // Cerrar la lectura del pipe actual en el proceso hijo
            open_redirs(pipex, pars->redir_list);
            child(pars, pipex, first, routes, all);
        } else {
            wait(NULL);
            close(pipex->tube[1]);
            fd_in = pipex->tube[0];
            first = 0;
            pars = pars->next;
        }
    }
    return(all->exit);
}

/*if (pars->next && (dup2(fds[1], 1) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))

if (pars->next && (dup2(fds[0], 0) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))
		return (perr("error: fatal\n"), 1);
*/