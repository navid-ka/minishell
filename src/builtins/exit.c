/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:50 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/26 11:49:55 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_exit(char *argv)
{
	if (!argv)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
}
