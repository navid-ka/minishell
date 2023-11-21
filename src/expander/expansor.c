/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/21 22:13:46 by bifrost          ###   ########.fr       */
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
		if (!expand)
			return ;
	}
	while (expand[i])
		*new_exp = charjoin(*new_exp, expand[i++]);
	free(expand);
}

void	expand(t_mch *sh, char **e, int i)
{
	int		j;
	char	*exp_arg;
	t_clean	q;

	j = 0;
	exp_arg = NULL;
	init_quotes(&q);
	while (e[i][j])
	{
		quote_updater(&q, e[i][j]);
		if ((e[i][j] == '"' && !q.scuote) || (e[i][j] == '\'' && !q.dcuote))
			j++;
		else if (e[i][j] == '$' && !q.scuote)
		{
			if (!e[i][j + 1])
				return ;
			expand_env(sh, &e[i][j], &exp_arg);
			j += iterate_env_var(&e[i][j]);
		}
		else
			exp_arg = charjoin(exp_arg, e[i][j++]);
	}
	free(e[i]);
	e[i] = exp_arg;
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
				if (is_ex(exp->args[i][j]))
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
