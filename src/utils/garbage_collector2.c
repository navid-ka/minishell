/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:47:49 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/09 21:30:21 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	free_tab(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
		args = NULL;
	}
}
