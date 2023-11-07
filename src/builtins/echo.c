/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 09:56:58 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	echo_without_option(t_mch *sh, char **str)
{
	int	i;

	i = 1;
	while (str[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", str[i]);
		if (str[i + 1] != NULL)
			ft_printf(STDOUT_FILENO, "%c", ' ');
		i++;
	}
	ft_printf(STDOUT_FILENO, "%c", '\n');
	sh->exit = EXIT_SUCCESS;
}

static void	echo_with_option(t_mch *sh, char **str)
{
	int	i;

	i = 2;
	while (str[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", str[i]);
		if (str[i + 1] != NULL)
			ft_printf(STDOUT_FILENO, "%c", ' ');
		i++;
	}
	sh->exit = EXIT_SUCCESS;
}

void	bt_echo(t_mch *sh, char **str)
{
	if (str[1] != NULL && ft_strncmp("-n", str[1], 3) == 0)
		echo_with_option(sh, str);
	else
		echo_without_option(sh, str);
}
