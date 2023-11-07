/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 09:54:46 by bifrost          ###   ########.fr       */
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
		if (!expand)
			return ;
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
	while (exp[i][j])
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
	exp[i] = exp_arg;
}

void	expansor(t_mch *sh)
{
	int			j;
	int			i;
	t_parser	*exp;

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
