/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:50 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 18:31:10 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_it_numeric(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) || ((line[i] == '-' || line[i] == '+')
			&& ft_isdigit(line[i + 1]) == 1))
		i++;
	else
		return (1);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == ' ' || line[i] == '\0')
	{
		while (line[i])
		{
			if (line[i] != ' ')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

static void	exit_message(t_mch *sh, int type, char *argument)
{
	if (type == 2)
	{
		ft_printf(2, "bash: exit: %s: numeric argument required\n", argument);
		exit(255);
	}
	else
	{
		ft_printf(2, "bash: exit: too many arguments\n");
		sh->exit = 1;
	}
}

void	bt_exit(t_mch *sh, char **argv)
{
	argv = sh->parser->args;

	if (argv[1])
	{
		if (ft_strcmp(argv[1], "--") == 0)
			exit(sh->exit);
		if (compare_exit(argv[1]) || is_it_numeric(argv[1]))
			exit_message(sh, 2, argv[1]);
		if (argv[2] != NULL)
			exit_message(sh, 1, argv[1]);
		else
			exit(ft_atoi(argv[1]));
	}
	else
		exit(sh->exit);
}
