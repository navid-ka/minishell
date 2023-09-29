/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 17:47:16 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_echo(t_lexer *lex)
{
	int endl;

	endl = 0;
	if (strcmp(lex->str, "-n") == 0)
		endl = 1;
	if (endl)
		lex = lex->next;
	ft_printf(1, "%s", lex->str);
	if (!endl)
		ft_printf(1, "\n");
}
