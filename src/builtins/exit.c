/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:50 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/31 15:51:19 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_exit(t_mch *sh, char *argv)
{
	if (!argv)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	} else
		exit(sh->exit);
}
