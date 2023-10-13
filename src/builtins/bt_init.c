/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:13:51 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/13 17:10:55 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	bt_is_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (true);
	if (ft_strcmp(argv[0], "env") == 0)
		return (true);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (true);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(argv[0], "export") == 0)
		return (true);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (true);
	if (ft_strcmp(argv[0], "exit") == 0)
		return (true);
	return (false);
}

void  bt_check_builtin(t_mch *sh)
{
	t_parser *cmd;

	cmd = sh->parser;
	/*if (ft_strcmp(argv[0], "cd") == 0)
		//bt_cd(argv, env);*/
		ft_printf(1, "BULTIN%s\n", cmd->args[0]);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		bt_env(sh);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		bt_echo(sh);
	/*if (ft_strcmp(argv[0], "pwd") == 0)
		ft_printf(1, "to implement\n");
		//bt_pwd();
	if (ft_strcmp(argv[0], "export") == 0)
		ft_printf(1, "to implement\n");
		//bt_export();
	if (ft_strcmp(argv[0], "unset") == 0)
		ft_printf(1, "to implement\n");
		//bt_unset();
	if (ft_strcmp(argv[0], "exit") == 0)
	ft_printf(1, "to implement\n");
		//bt_exit();*/
}
