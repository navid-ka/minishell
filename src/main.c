/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:38 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/03 18:24:20 by nkeyani-         ###   ########.fr       */
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
	return (sh.exit);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//lexerizar
