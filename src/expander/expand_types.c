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

void	expand_args(t_mch *sh, t_parser *exp)
{
	int	i;
	int	j;

	i = -1;
	while (exp->args[++i])
	{
		j = 0;
		while (exp->args[i][j])
		{
			if (is_ex(exp->args[i], j))
			{
				expand(sh, &(exp->args[i]));
				break ;
			}
			j++;
		}
	}
}

void	expand_redir(t_mch *sh, t_parser *exp)
{
	int	j;

	j = 0;
	if (exp->redir_list)
	{
		while (exp->redir_list->file[j])
		{
			if (is_ex(exp->redir_list->file, j) \
				&& exp->redir_list->type != HERE_DOC)
			{
				expand(sh, &(exp->redir_list->file));
				break ;
			}
			j++;
		}
	}
}
