/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:35:34 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/30 13:53:01 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(t_mch *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_or_update_env(sh, "PWD", pwd);
	free(pwd);
}

void	home(t_mch *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_or_update_env(sh, "OLDPWD", pwd);
	chdir(find_in_env_variables(sh, "HOME"));
	update_pwd(sh);
	free(pwd);
}

void	bt_cd(t_mch *sh, char **arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (arg[1] == NULL)
		home(sh);
	else if (arg[2] != NULL)
		ft_printf(2, "bash: cd: Too many arguments\n");
	else if (ft_strncmp("-", arg[1], 2) == 0)
	{
		if (chdir(find_in_env_variables(sh, "OLDPWD")) == -1)
			ft_printf(STDERR_FILENO, "%s", "cd: OLDPWD not set\n");
		add_or_update_env(sh, "OLDPWD", pwd);
		update_pwd(sh);
	}
	else
	{
		add_or_update_env(sh, "OLDPWD", pwd);
		if (chdir(arg[1]) == -1)
		{
			ft_printf(STDERR_FILENO, CD, arg[1]);
			sh->exit = 1;
		}
		update_pwd(sh);
	}
	free(pwd);
}
