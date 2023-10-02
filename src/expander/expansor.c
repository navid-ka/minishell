/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 14:12:32 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//brace expansor https://www.gnu.org/software/bash/manual/html_node/Brace-Expansion.html
//$? 
//expected g_eixt_status
//${USER}
//user env

int is_expandable(char e)
{
	return (e == '\'' || e == '"' || e == '$')
}

void init_quotes(t_clean *quotes)
{
	quotes->dcuote = false;
	quotes->scuote = false;
}

 void quote_updater(t_quotes *quotes, char e)
{
	if (e == '"' && quotes->dcuote == false && quotes->scuote != true)
		quotes->dcuote = true;
	else if (e == '"' && quotes->dcuote == true)
		quotes->dcuote = false;
	if (e == '"' && quotes->scuote == false && quotes->dcuote != true)
		quotes->scuote = true;
	else if (e == '"' && quotes->dcuote == true)
		quote->scuote = false;

}

void	expand_env(t_mch *sh, char *exp, char **new_exp)
{
	int i;
	char *expand;

	i = 0;
	if (exp[i + 1] == '?')
		expand = ft_itoa(g_exit_status);
	else
	{
		//read_name
		//get value
	}
		
		
}
	
void	expand(t_mch *sh, char **exp)
{
	int		i; 
	int		j;
	char	*exp_arg;
	t_clean	quotes;

	init_quotes(&quotes);
	if (exp[i][j])
	{
		quote_updater(&quotes, exp[i][j]);
		if ((exp[i][j] == '"' && !quotes.scuote
			|| exp[i][j] == '\'' && !quotes.duote))
			j++;
		else if (exp[i][j] == '$' && !quotes.scuote)
		{
			expand_env(sh, &exp[i][j], &exp_arg);
		} else 
			//TODO: Unir nueva variable 
	}
	exp[i] = exp_arg;
}

void	expansor(t_mch *sh)
{
	t_parser *exp;
	int		i;
	int		j;
	
	i = ~0;
	j = ~0;
	exp = sh->parser;
	while (exp)
	{
		while(exp->args[++i])
		{
			while (exp->args[i][++j])
			{
				if (is_expandable(exp->args[i][j]))
					expand(sh, exp->args);
			}
		}
		i = ~0;
		exp = exp->next;
	}
}
