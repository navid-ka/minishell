/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/01 12:54:58 by bifrost          ###   ########.fr       */
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

void	print_sort_print(t_env *env)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				tmp_name = tmp->name;
				tmp_value = tmp->value;
				tmp->name = tmp->next->name;
				tmp->value = tmp->next->value;
				tmp->next->name = tmp_name;
				tmp->next->value = tmp_value;
				tmp = env;
			}
		}
		tmp = tmp->next;
	}
}

void	print_env(t_mch *sh)
{
	t_env	*env;

	env = sh->env;
	print_sort_print(env);
	while (env != NULL)
	{
		if (env->value != NULL)
			ft_printf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", \
				env->name, env->value);
		else
			ft_printf(STDOUT_FILENO, "declare -x %s\n", env->name);
		env = env->next;
	}
	ft_printf(STDOUT_FILENO, "\n");
}

bool	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (false);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if ((name[i] == '+' || name[i] == '=') && name[i + 1] != '\0')
				return (false);
		}
		i++;
	}
	return (true);
}
