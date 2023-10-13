/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/10 10:33:36 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// this will help me find the index of '='
int	pos_chr(const char *s, int c)
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

//in expansor.c maybe move to env_utils
int	env_index(t_mch *sh, char *env_name);

void    update_env_value;
void    append_env;
void    print_export(void)
{
	t_mch shell;
	int	i; 
	
	i = ~0;
	while (sh.env[++i])
		ft_printf(1, "declare -x %s", sh.env[i]);
}

//  export alone joins "declare -x"  with normal env
void	bt_export(t_mch *sh)
{
	int	i;
	t_parser *exp;

	i = 0;
	exp = sh->parser;
    if (exp->args[1] == NULL)
        print_export();
	while (exp)
	{
        if (ft_strncmp(exp->args[1], sh->env[i], pos_chr(sh->env[i], '=')) == 0)
            update_env_value
        else
            append_env
        exp = exp->next;
	}
}
