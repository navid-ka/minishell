/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/16 12:01:46 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	iterate_env_var(char *arg)
{
	int	i;

	i = 1;
	if (arg[1] == '?')
		return (2);
	while (arg[i] && arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
		i++;
	return (i);
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
	return (env_name);
}

void	expand_env(t_mch *sh, char *exp, char **new_exp)
{
	int		i;
	char	*expand;
	char	*env_name;

	i = 0;
	if (exp[1] == '?')
		expand = ft_itoa(sh->exit);
	else
	{
		env_name = get_env_name(exp);
		if (!env_name)
		{
			free(env_name);
			return ;
		}
		expand = ft_strdup(find_in_env_variables(sh, env_name));
		free(env_name);
	}
	while (expand[i])
		*new_exp = charjoin(*new_exp, expand[i++]);
	free(expand);
}

void	expand(t_mch *sh, char **exp, int i)
{
	int		j;
	char	*exp_arg;
	t_clean	quotes;

	j = 0;
	exp_arg = NULL;
	init_quotes(&quotes);
	if (exp[i][j])
	{
		quote_updater(&quotes, exp[i][j]);
		if ((exp[i][j] == '"' && !quotes.scuote) \
			|| (exp[i][j] == '\'' && !quotes.dcuote))
			j++;
		else if (exp[i][j] == '$' && !quotes.scuote)
		{
			if (!exp[i][j + 1])
				return ;
			expand_env(sh, &exp[i][j], &exp_arg);
			j += iterate_env_var(&exp[i][j]);
		}
		else
			exp_arg = charjoin(exp_arg, exp[i][j++]);
	}
	free(exp[i]);
	exp[i] = NULL;
	exp[i] = exp_arg;

}

void	expansor(t_mch *sh)
{
	int	j;
	int	i;
	t_parser *exp;


	i = ~0;
	exp = sh->parser;
	while (exp)
	{
		while (exp->args[++i])
		{
			j = ~0;
			while (exp->args[i][++j])
			{
				if (is_expandable(exp->args[i][j]))
				{
					expand(sh, exp->args, i);
					break ;
				}
			}
		}
		i = ~0;
		exp = exp->next;
	}
}
