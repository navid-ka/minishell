/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:38 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 09:50:34 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mch	sh;

	(void)argv;
	if (argc != 1)
	{
		printf("Too many arguments\n");
		exit (1);
	}
	sh.exit = 0;
	minishell(&sh, env);
	exit (sh.exit);
}
