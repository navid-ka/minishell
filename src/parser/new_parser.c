/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 19:47:34 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_pipes(t_lexer *lex)
{
	int	pipes;

	pipes = 0;
	while (lex)
	{
		if (lex->type == PIPE)
			pipes++;
		lex = lex->next;
	}
	return (pipes);
}

// static void cmd_init(t_cmd *cmd, int pipes)
// {
	
// }

static void	parse(t_lexer *lex, t_parser *parser)
{
	t_lexer *tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			int i = 0;
			parser->args = malloc(sizeof(char *) * 50);
			while (tmp && tmp->type == CMD) {
				parser->args[i++] = ft_strdup(tmp->str);
				tmp = tmp->next;
			}
			parser->cmd = parser->args[0];
			parser = parser->next;
		}
		else if (tmp->type == REDIR)
		{
			parser->next->red.input = tmp->type;
			tmp = tmp->next;
		}
	}
}

void	parser(t_mch *sh, t_lexer *lex)
{
	int	pipes;

	pipes = count_pipes(lex); //LIKE
	sh->parser = malloc(sizeof (t_parser) * (pipes + 1));
	//cmd_init(sh->cmd, pipes + 1);
	parse(lex, sh->parser);
}

