/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:16:24 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/07 10:39:28 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	serror(char *s)
{
	ft_printf(2, "bash: syntax error near unexpected token `%s\'\n", s);
	return (2);
}

int	syntax_handler(t_lexer *tok, int *pipes, int *redirs)
{
	while (tok)
	{
		if (tok && (tok->type == TRUNC || tok->type == APPEND \
			|| tok->type == HERE_DOC || tok->type == INPUT))
		{
			if (*redirs == 1)
				return (serror(tok->str));
			*redirs = 1;
		}
		if (tok && tok->type == CMD)
		{
			*pipes = 0;
			*redirs = 0;
		}
		if (tok && tok->type == PIPE)
		{
			if (*pipes == 1 || *redirs == 1)
				return (serror(tok->str));
			*pipes = 1;
		}
		tok = tok->next;
	}
	return (0);
}

int	check_syntax(t_lexer *tok)
{
	t_lexer	*tmp;
	int		pipes;
	int		redirs;

	tmp = tok;
	if (tmp && tmp->type == PIPE)
		return (serror("|"));
	redirs = 0;
	pipes = 0;
	if (syntax_handler(tmp, &pipes, &redirs) != 0)
		return (2);
	if (redirs >= 1)
		return (serror("newline"));
	if (pipes >= 1)
		return (serror("|"));
	return (0);
}
