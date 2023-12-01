/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/01 12:56:00 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_plus_equal(t_mch *sh, char *name, char *value)
{
	t_env	*env;
	char	*old_value;
	char	*env_value;

	env_value = find_in_env_variables(sh, name);
	if (!env_value)
	{
		add_or_update_env(sh, name, value);
		return ;
	}
	env = sh->env;
	if (!value)
		value = ft_strdup("");
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
			&& ft_strlen(env->name) == ft_strlen(name))
		{
			old_value = env->value;
			env->value = ft_strjoin(old_value, value);
			free(old_value);
			return ;
		}
		env = env->next;
	}
}

void	handle_arg(t_mch *sh, char *arg)
{
	char	**v;
	char	*name;

	v = ft_split(arg, '=');
	if (!is_valid_identifier(v[0]))
		ft_printf(2, EXPORT, v[0], v[1]);
	else
	{
		if (ft_strchr(v[0], '+'))
		{
			name = ft_substr(v[0], 0, ft_strchr(v[0], '+') - v[0]);
			export_plus_equal(sh, name, v[1]);
			free(name);
		}
		else
			add_or_update_env(sh, v[0], v[1]);
	}
	free_tab(v);
}

void	bt_export(t_mch *sh, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		print_env(sh);
	else
	{
		while (args[i] != NULL)
		{
			handle_arg(sh, args[i]);
			i++;
		}
	}
}
