/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:09:24 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/03 13:33:09 by nkeyani-         ###   ########.fr       */
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
	parser->red = malloc(sizeof(t_redir) * 1);
	parser->args = malloc(sizeof(t_parser) * 1);
	while (tmp)
	{
		if (tmp && (tmp->type == CMD))
		{
			
			parser->red->input = 0;
			parser->red->outfile = 0;
			int i = 0;
			while (tmp && tmp->type == CMD) {
				parser->args[i++] = ft_strdup(tmp->str);
				tmp = tmp->next;
			}
			parser->args[i] = NULL;
			parser->cmd = ft_strdup(parser->args[0]);
			if (tmp && tmp->type == INPUT)
			{
				parser->red->input = tmp->type;
				parser->red->infile = ft_strdup(tmp->next->str);
				tmp += 2;
			}
			else{
				/*parser->red->output = tmp->type;
				if (tmp && (tmp->type == TRUNC || tmp->type == APPEND))
				{
					parser->red->outfile = ft_strdup(tmp->next->str);
					tmp = tmp->next->next;
				}
				tmp = tmp->next;
				parser = parser->next;*/
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

