/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:38 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/27 10:59:50 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// void create_cmd(char *argv, t_cmd *cmd)
// {
//   int quotes_count;

//   quotes_count = 0;
//   quotes_count = count_quotes(argv);
//   cmd->argv = split_cmd(argv, quotes_count);
//   if (!bt_is_builtin(cmd->argv))
//     ft_printf(1, "Env execs?/n");
//   else
//     bt_check_builtin(cmd->argv, NULL);
//     //TODO: aqui debemos hacer algo si no es builtin puede que ejecutarlo desde env?
//   // o quizas me he adelantado y hay que hacer mas cosas
// }

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	minishell(env);
	return (0);
}

//hacer echo y exit
//arreglar errores para errores en los subshells
//tokenizar
