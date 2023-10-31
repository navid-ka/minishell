/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:38 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/31 09:48:22 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	main(int argc, char **argv, char **env)
{
	t_mch	sh;

	(void)argc;
	(void)argv;
	sh.exit = 0;
	minishell(&sh, env);
	exit (sh.exit);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//lexerizar
