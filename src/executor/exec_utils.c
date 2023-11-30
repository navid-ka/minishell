/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:20:57 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/11/30 14:58:50 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	load_routes(t_pipe *pipex, t_mch *all)
{
	char	*path_env;

	path_env = get_path_env_value(all);
	if (path_env == NULL)
		return ;
	pipex->routes = ft_split(path_env, ':');
	free(path_env);
	path_env = NULL;
}

char	*get_args(t_parser *pars, char **routes)
{
	char	*args;

	args = find_cmd(routes, pars->args[0]);
	if (!pars->args[0])
		exit(127);
	return (args);
}

void	close_pipes(t_pipe *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

//el ultimo exit_code dónde queda?
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
