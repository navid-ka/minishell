/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/15 00:31:39 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_echo(t_mch *sh)
{
	t_parser *cmd;
	int		i;
	
	i = 1;
	cmd = sh->parser;
	while (cmd)
	{
		ft_printf(1, "%s\n", cmd->args[i]);
		i++;
		cmd = cmd->next;
	}
}
