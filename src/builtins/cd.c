/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:35:34 by bifrost           #+#    #+#             */
/*   Updated: 2023/10/16 11:38:21 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_old_pwd(t_mch *sh, char *old_pwd, char *new_pwd)
{
	t_env	*env;

	env = sh->env;
	if (old_pwd == NULL)
	{
		add_or_update_env(sh, "OLDPWD", new_pwd);
		return ;
	}
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_pwd);
			return ;
		}
		env = env->next;
	}
}

void	bt_cd(t_mch *sh, char **arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (arg[1] == NULL)
	{
		update_old_pwd(sh, find_in_env_variables(sh, "OLDPWD"), pwd);
		chdir(find_in_env_variables(sh, "HOME"));
	}
	else if (ft_strncmp("-", arg[1], 2) == 0)
	{
		if (chdir(find_in_env_variables(sh, "OLDPWD")) == -1)
			ft_printf(STDERR_FILENO, "%s", "cd: OLDPWD not set\n");
		update_old_pwd(sh, find_in_env_variables(sh, "OLDPWD"), pwd);
	}
	else
	{
		update_old_pwd(sh, find_in_env_variables(sh, "OLDPWD"), pwd);
		if (chdir(arg[1]) == -1)
		{
			ft_printf(STDERR_FILENO,
				"cd: %s: No such file or directory\n", arg[1]);
			sh->exit = 1;
		}
	}
	free(pwd);
}
