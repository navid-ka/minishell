#include "minishell.h"

int	is_redir(int type)
{
	if (type == TRUNC || type == APPEND \
		|| type == HERE_DOC || type == INPUT)
		return (1);
	return (0);
}

int count_pipes(t_lexer *lex)
{
	int n;
	t_lexer *tmp;

	tmp = lex;
	n  = 1;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		tmp = tmp->next;
	} 
	return (n);
}

int	count_words(t_lexer *tok)
{
	t_lexer	*first;
	int		words;

	first = tok;
	words = 0;
	while (first)
	{
		words++;
		first = first->next;
	}
	return (words);
}

t_lexer	*tok_type_changer(t_lexer *tmp)
{
	t_lexer	*lex;

	lex = tmp;
	while (lex)
	{
		if (lex && is_redir(lex->type))
		{
			if (lex && !is_redir(lex->next->type))
			{
				lex->next->type = lex->type; // change the type of the next token
				lex  = lex->next;
			}
		}
		lex  = lex->next;
	}
	return (tmp);
}

t_parser *create_parser(void)
{
	t_parser *parser;

	parser = ft_calloc(sizeof(t_parser), 1);
	parser->args = NULL;
	parser->next = NULL;
	return (parser);
}

void process_cmd_args(t_lexer *tmp, t_parser *parser)
{
	t_lexer *lex;
	int i = 0;

	lex = tmp;
	//parser->args = (char **)ft_calloc((count_words(tmp) + 1), sizeof(char *));
	if (!parser->args)
		return;
	while (lex && lex->type != PIPE)
	{
		if (lex->type == CMD)
		{
			parser->args[i] = ft_strdup(lex->str);
			i++;
		}
		lex = lex->next;
	}
	parser->args[i] = NULL;
	lex = tmp; // Reset lex to the start of the tokens list
}

void process_redirections(t_lexer *tmp, t_redir **red)
{
	t_redir *new_redir;

	if (is_redir(tmp->type))
	{
		if (tmp->next != NULL) 
		{
			new_redir = create_redir_node(tmp->next->str, tmp->type);
			if (new_redir != NULL)
			{
				redir_lstadd_back(red, new_redir);
			}
		}
	}
}
void process_tokens(t_lexer *tmp, t_parser *parser, t_redir *red)
{
	t_lexer *start;

	start = tmp;
	while (tmp != NULL)
	{
		if (tmp && tmp->type == PIPE)
		{
			parser_lstadd_back(&(parser), parser);
			parser = create_parser();
			tmp = tmp->next;
			start = tmp;
			continue;
		}
		process_cmd_args(start, parser);
		if (is_redir(tmp->type))
			process_redirections(tmp, &red);
		tmp = tmp->next;
	}
	parser_lstadd_back(&(parser), parser);
	red = NULL;
	parser->redir_list = red;
}

void parser(t_mch *sh, t_lexer *lex)
{
	t_lexer *tmp;
	t_redir *red;
	t_parser *parser;

	sh->lex = lex;
	parser = NULL;
	tmp = sh->lex;
	tmp = tok_type_changer(tmp);
	red = NULL;
	red = ft_calloc(sizeof(t_redir) + 1, 1);
	sh->red = red;
	parser = create_parser();
	parser->args = (char **)ft_calloc((count_words(tmp) + 1), sizeof(char *));
	process_tokens(tmp, parser, red);
	sh->parser = parser;
}
