/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:50:02 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/17 19:14:13 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bt_env(t_mch *sh)
{
	t_env	*env;

	env = sh->env;
	while (env != NULL)
	{
		if (ft_printf(STDOUT_FILENO, "%s=%s\n", env->name, env->value) == 0)
		{
			sh->exit = EXIT_FAILURE;
			return ;
		}
		env = env->next;
	}
	ft_printf(STDOUT_FILENO, "\n");
	sh->exit = EXIT_SUCCESS;
}
