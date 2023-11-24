#include <minishell.h>

void	dup_original_stds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

int	dup_custom_redirections(t_pipe *data, t_redir *temp)
{
	if (temp->type == INPUT || temp->type == HERE_DOC)
	{
		data->fd_infile = open(temp->file, O_RDONLY);
		if (data->fd_infile < 0)
			return (1);
		dup2(data->fd_infile, STDIN_FILENO);
		close(data->fd_infile);
	}
	else if (temp->type == TRUNC || temp->type == APPEND)
	{
		if (temp->type == TRUNC)
			data->fd_outfile = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->fd_outfile = open(temp->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (data->fd_outfile < 0)
			return (1);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
	return (0);
}

int	manage_redirections(t_parser *commands, t_pipe *data, int out)
{
	t_redir	*temp;

	if (commands->next != NULL)
		dup2(data->fd[1], STDOUT_FILENO);
	close_pipes(&data);
	temp = commands->redir_list;
	while (temp)
	{
		if (dup_custom_redirections(data, temp) == 1)
		{
			/*if (out == FT_RETURN)
				return (perror_return(data, 1, temp->file));
			else
				perror_exit(data, EXIT_FAILURE, temp->file);
			*/
			printf("hola");
		}
		temp = temp->next;
	}
	return (0);
}

void	wait_childs(t_pipe *data, int *exit_s)
{
	int	i;
	int	status;

	dup2(data->dup_stdin, STDIN_FILENO);
	dup2(data->dup_stdout, STDOUT_FILENO);
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	free(data->pid);
	if (WIFEXITED(status))
		*exit_s = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			*exit_s = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			*exit_s = 131;
			ft_printf("Quit: 3\n");
		}
	}
}

void	new_command(t_parser *commands, t_pipe *data, t_env *envp, int *exit_s)
{
	int		exit_code;
	char	*path;

	init_signals(CHILDS);
	manage_redirections(commands, data, FT_EXIT);
	if (is_builtin(commands))
		execute_builtins(commands->args, envp, exit_s, FT_EXIT);
	exit_code = search_path(commands->args[0], envp->env, &path);
	if (exit_code == CMD_NOT_FOUND)
		error_exit(data, CMD_NOT_FOUND, commands->args[0], MSSG_CMD_NOT_FOUND);
	else if (exit_code == NO_SUCH_FILE)
		error_exit(data, CMD_NOT_FOUND, commands->args[0], MSGG_NO_SUCH_FILE);
	else if (exit_code == IS_A_DIR)
		error_exit(data, CMD_NO_ACCESS, commands->args[0], MSGG_IS_A_DIR);
	else if (exit_code != 0)
		perror_exit(data, exit_code, commands->args[0]);
	if (execve(path, commands->args, envp->env) == -1)
		perror_exit(data, EXIT_FAILURE, "Execve");
}

int	exec_one_builtin(t_parser *commands, t_pipe *data, t_env *envp, int *exit_s)
{
	if (manage_redirections(commands, data, FT_RETURN) == 1)
	{
		*exit_s = 1;
		dup2(data->dup_stdin, STDIN_FILENO);
		dup2(data->dup_stdout, STDOUT_FILENO);
		return (0);
	}
	free(data->pid);
	execute_builtins(commands->args, envp, exit_s, FT_RETURN);
	dup2(data->dup_stdin, STDIN_FILENO);
	dup2(data->dup_stdout, STDOUT_FILENO);
	return (0);
}

int	execute_commands(t_parser *commands, t_env *envp, int *exit_s)
{
	t_pipe	data;
	int		i;

	//if (init_data(&data, commands) == 1)
		//return (1);
	dup_original_stds(&data.dup_stdin, &data.dup_stdout);
	//if (data.npipes == 1 && is_builtin(commands))
	//	return (exec_one_builtin(commands, &data, envp, exit_s));
	(1 && (i = 0));
	while (commands)
	{
		if (pipe(data.tube) == -1)
			return (0);
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (0);
		else if (data.pid[i] == 0)
			new_command(commands, &data, envp, exit_s);
		dup2(data.fd[0], STDIN_FILENO);
		close_pipes(&data);
		commands = commands->next;
		i++;
	}
	wait_childs(&data, exit_s);
	return (0);
}