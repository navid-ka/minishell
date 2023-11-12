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
			if (lex->next)
			{
				lex->next->type = lex->type; // change the type of the next token
				lex = lex->next->next;
			}
		}
		if (lex)
			lex  = lex->next;
	}
	return (lex);
}

t_parser *create_parser(void)
{
    t_parser *parser = ft_calloc(sizeof(t_parser) + 1, 1);
    parser->args = NULL;
    parser->next = NULL;
    return parser;
}

void process_cmd_args(t_lexer *tmp, t_parser *parser)
{
    t_lexer *lex;
    int i = 0;

    lex = tmp;
    parser->args = (char **)ft_calloc((count_words(tmp) + 1), sizeof(char *));
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
    if (is_redir(tmp->type))
    {
        if (tmp->next != NULL) 
        {
            t_redir *new_redir = create_redir_node(tmp->next->str, tmp->type);
            if (new_redir != NULL)
            {
                redir_lstadd_back(red, new_redir);
            }
		}
    }
}

void process_tokens(t_mch *sh, t_lexer *tmp, t_parser *parser, t_redir *red)
{
    t_lexer *start = tmp;
    while (tmp != NULL)
    {
        if (tmp && tmp->type == PIPE)
        {
            parser_lstadd_back(&(sh->parser), parser);
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
    parser_lstadd_back(&(sh->parser), parser);
    red = NULL;
}

void parser(t_mch *sh, t_lexer *lex)
{
    t_lexer *tmp;
    t_redir *red;
    t_parser *parser;

    sh->lex = lex;
    tmp = sh->lex;
    tok_type_changer(tmp);
    red = ft_calloc(sizeof(t_redir) + 1, 1);
    red->next = NULL;
    sh->red = red;
    sh->parser = ft_calloc(sizeof(t_parser) + count_pipes(tmp), 1);
    parser = create_parser();
    process_tokens(sh, tmp, parser, red);
    sh->parser = parser;
}
