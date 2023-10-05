/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/03 17:24:58 by nkeyani-         ###   ########.fr       */
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