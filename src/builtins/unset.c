/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 01:03:04 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/01 13:01:09 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(t_mch *sh, char *arg)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	while (!ft_strchr("|<> \"\'$?=", arg[i]))
		i++;
	if (i > 0)
		name = ft_substr(arg, 0, i);
	value = find_in_env_variables(sh, name);
	free(name);
	return (ft_strdup(value));
}

void	unset_var(t_mch *sh, char *var)
{
	t_env	*node;
	t_env	*tmp;

	node = sh->env;
	tmp = NULL;
	if (ft_strcmp(node->name, var) == 0)
	{
		sh->env = sh->env->next;
		unset_free(node);
		return ;
	}
	while (node != NULL && ft_strcmp(node->name, var) != 0)
	{
		tmp = node;
		node = node->next;
	}
	if (node == NULL)
		return ;
	tmp->next = node->next;
	unset_free(node);
}

void	bt_unset(t_mch *sh, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_var(sh, args[i]);
		i++;
	}
}
