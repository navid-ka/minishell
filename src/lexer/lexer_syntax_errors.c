/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:20:55 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/21 20:42:51 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_error(void)
{
	ft_printf(STDERR_FILENO, "minishell: Invalid Syntax not closed quotes\n");
}

char	*lexer_end_subshell(char *line)
{
	if (!line)
		return (NULL);
	while (*line)
	{
		if (*line == '&')
			return (line);
		if (*line == '|')
			return (line);
		if (*line == '<')
			return (line);
		if (*line == '>')
			return (line);
		++line;
	}
	return (line);
}

int	quote_checker(char *line)
{
	bool	dcuotes;
	bool	scuotes;

	dcuotes = false;
	scuotes = false;
	while (*line)
	{
		if (*line == '"' && !scuotes)
			dcuotes = !dcuotes;
		else if (*line == '\'' && !dcuotes)
			scuotes = !scuotes;
		++line;
	}
	if (dcuotes || scuotes)
		return (0);
	return (1);
}
