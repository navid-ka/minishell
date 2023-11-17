/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/17 21:30:39 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	echo_without_option(t_mch *sh, char **str, int i)
{
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

static void	echo_with_option(t_mch *sh, char **str, int i)
{
	while (str[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", str[i]);
		if (str[i + 1] != NULL)
			ft_printf(STDOUT_FILENO, "%c", ' ');
		i++;
	}
	sh->exit = EXIT_SUCCESS;
}

int is_n(char **str, int *i)
{
	int j;
	int flag;

	flag = 0;
	while (str[*i][0] == '-')
	{
		j = 1;
		while (str[*i][j])
		{
			if (str[*i][j] != 'n')
				return (flag);
			j++;
		}
		*i += 1;
		flag = 1;
	}
	return (flag);
}
void	bt_echo(t_mch *sh, char **str)
{
	int i = 1;

	if (str[i] != NULL && is_n(str, &i))
	{
		echo_with_option(sh, str, i);
	}
	else
		echo_without_option(sh, str, i);
}
