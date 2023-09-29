/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:21:30 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 15:06:52 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int	pos_chr(const char *s, int c)
{
	int	i;

	if (!s)
		return (-2);
	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

t_env	*append_env(char *key, char *value)
{
	t_env *ls;

	ls = ft_calloc(sizeof(t_env), 1);
	if (!ls)
		return (NULL);
	ls->key = key;
	ls->value = value;
	return (ls);
}*/

void	get_env(t_mch *sh, char **env)
{
	int	i;
	int	j;

	i = ~0;
	j = ~0;
	while (env[++j])
		;
	sh->env = ft_calloc(sizeof(sh->env + 1), j);
	while (env[++i])
		sh->env[i] = ft_strdup(env[i]);
	sh->env[i] = NULL;
	/*i = ~0;
	while (sh->env[++i])
		ft_printf(1, "%s\n", sh->env[i]);*/
}

