/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/01 14:14:25 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//comando < archivo_de_entrada
//comando > archivo_de_salida
//comando >> archivo_de_salida
//comando << DELIMITADOR

static int	count_pipes(t_lexer *lexer)
{
	int	pipes;

	pipes = 0;
	t_lexer *lex = lexer;
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
		ft_printf(0, "uwu1\n");
		if (tmp->type == CMD)
		{
			ft_printf(0, "uwu2\n");
			parser->red = malloc(sizeof(t_redir) * 1);
			parser->red->input = 0;
			parser->red->outfile = 0;
			ft_printf(0, "uwu3\n");
			int i = 0;
			parser->args = malloc(sizeof(char *) * 50);
			ft_printf(0, "uw4u\n");
			while (tmp && tmp->type == CMD) {
				parser->args[i++] = ft_strdup(tmp->str);
				tmp = tmp->next;
			}
			ft_printf(0, "uwu5\n");
			parser->cmd = parser->args[0];
			if (tmp && tmp->type == INPUT)
			{
				ft_printf(0, "uwu7\n");
				parser->red->input = tmp->type;
				parser->red->infile = tmp->next->str;
				tmp += 2;
				ft_printf(0, "uwu6\n");
			}
			else{
				parser->red->output = tmp->type;
				if (tmp && (tmp->type == TRUNC || tmp->type == APPEND))
				{
					parser->red->outfile = tmp->next->str;
					tmp += 2;
				}
				parser = parser->next;
			}
		}
		else if (tmp && tmp->type == PIPE)
		{
			parser->red->input = tmp->type;
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

