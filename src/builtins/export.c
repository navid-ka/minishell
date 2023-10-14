/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/14 19:19:29 by bifrost          ###   ########.fr       */
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
}

void	bt_export(t_mch *sh, char **args)
{
	int	i;
	char **vars;

	i = 0;
 	if (args[1] == NULL)
		print_env(sh);
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			vars = ft_split(args[i], '=');
			if (ft_isdigit(vars[0][0]) || vars[0][0] == '_')
				ft_printf(2,"export: `%s=%s': not a valid identifier\n",vars[0], vars[1]);
			else
				add_or_update_env(sh, vars[0], vars[1]);
			free_tab(vars);
			i++;
		}
       
    }
}
	