/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/22 19:36:13 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_ex(const char *str, int i)
{
	if (str[i] == '\'' || str[i] == '"' || str[i] == '$')
		return (1);
	return (0);
}

void	init_quotes(t_clean *quotes)
{
	quotes->dcuote = false;
	quotes->scuote = false;
}

void	quote_updater(t_clean *quotes, char e)
{
	if (e == '"' && !quotes->dcuote && quotes->scuote != true)
		quotes->dcuote = true;
	else if (e == '"' && quotes->dcuote == true)
		quotes->dcuote = false;
	if (e == '\'' && !quotes->scuote && quotes->dcuote != true)
		quotes->scuote = true;
	else if (e == '\'' && quotes->scuote == true)
		quotes->scuote = false;
}

char	*find_in_env_variables(t_mch *sh, char *variable_name)
{
	t_env	*env;
	int		env_name_len;
	int		var_name_len;

	if (variable_name == NULL)
		return (NULL);
	env = sh->env;
	var_name_len = ft_strlen(variable_name);
	while (env != NULL)
	{
		env_name_len = ft_strlen(env->name);
		if (ft_strncmp(env->name, variable_name, env_name_len) == 0
			&& (env_name_len == var_name_len))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_name(char *arg)
{
	int		i;
	char	*env_name;

	i = 1;
	env_name = NULL;
	while (arg[i] && arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
	{
		env_name = charjoin(env_name, arg[i]);
		i++;
	}
	if (!env_name)
		return (NULL);
	return (env_name);
}
