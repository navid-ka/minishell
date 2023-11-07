/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:21:30 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 10:40:12 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*last_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env_to_list(t_env **env, t_env *new_env)
{
	if (new_env == NULL)
		return ;
	if (*env == NULL)
	{
		*env = new_env;
		return ;
	}
	last_env(*env)->next = new_env;
}

void	get_env(t_mch *sh, char **env)
{
	t_env	*sh_env;
	int		i;

	i = ~0;
	while (env[++i] != NULL)
	{
		sh_env = malloc(sizeof(t_env));
		sh_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		sh_env->value = ft_strdup(getenv(sh_env->name));
		sh_env->next = NULL;
		add_env_to_list(&sh->env, sh_env);
	}
}
