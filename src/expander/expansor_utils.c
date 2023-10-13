/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/13 15:54:26 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_expandable(char e)
{
	return ((e == '\'' || e == '"' || e == '$'));
}

void	init_quotes(t_clean *quotes)
{
	quotes->dcuote = false;
	quotes->scuote = false;
}

void	quote_updater(t_clean *quotes, char e)
{
	if (e == '"' && quotes->dcuote == false && quotes->scuote != true)
		quotes->dcuote = true;
	else if (e == '"' && quotes->dcuote == true)
		quotes->dcuote = false;
	if (e == '"' && quotes->scuote == false && quotes->dcuote != true)
		quotes->scuote = true;
	else if (e == '"' && quotes->dcuote == true)
		quotes->scuote = false;
}

void print_expansor(t_mch *sh)
{
	t_parser *ptr;
	
	int i = 0;
	ptr = sh->parser;
	while (ptr)
	{
		while (ptr->args[i])

			printf("EXPANDER: %s", ptr->args[i++]);
		ptr = ptr->next;
	}
}
