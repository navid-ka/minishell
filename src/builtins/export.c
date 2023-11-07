/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 10:08:12 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_or_update_env(t_mch *sh, char *name, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = sh->env;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0
			&& ft_strlen(env->name) == ft_strlen(name))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	add_env_to_list(&sh->env, new_env);
}

void	print_env(t_mch *sh)
{
	t_env	*env;

	env = sh->env;
	while (env != NULL)
	{
		ft_printf(STDOUT_FILENO, "declare -x %s=%s\n", env->name, env->value);
		env = env->next;
	}
	ft_printf(STDOUT_FILENO, "\n");
}

void	bt_export(t_mch *sh, char **args)
{
	int		i;
	int		j;
	char	**v;

	i = 1;
	if (args[i] == NULL)
		print_env(sh);
	else
	{
		j = -1;
		while (args[i] != NULL)
		{
			v = ft_split(args[i], '=');
			while (v[++j] != NULL)
				if (ft_strchr(v[j], '+') != NULL)
					return ((void)ft_printf(2, EXPORT, v[j], v[1]),
						free_tab(v));
			if (ft_isdigit(v[0][0]) || v[0][0] == '_')
				ft_printf(2, EXPORT, v[0], v[1]);
			else
				add_or_update_env(sh, v[0], v[1]);
			free_tab(v);
			i++;
		}
	}
}
