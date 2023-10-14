/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/14 18:19:15 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_echo(t_mch *sh)
{
	int endl;
	t_parser *cmd;
	
	cmd = sh->parser;
	endl = 0;
	if (strcmp(cmd->args[0], "-n") == 0)
		endl = 1;
	if (endl)
		cmd = cmd->next;
	ft_printf(1, "%s", cmd->args[1]);
	if (!endl)
		ft_printf(1, "\n");

}
