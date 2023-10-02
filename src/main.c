/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:38 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 17:47:16 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Global variable
int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mch	sh;

	(void)argc;
	(void)argv;
	minishell(&sh, env);
	return (g_exit_status);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//lexerizar
