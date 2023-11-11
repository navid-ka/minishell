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

char **cmd(t_lexer *lex)
{
    char **args;
    int i;

    i = 0;
    args = (char **)ft_calloc((count_words(lex) + 2), sizeof(char *));
    while (lex)
    {
        if (lex->type == CMD)
        {
            args[i++] = ft_strdup(lex->str);
        }
        else if (is_redir(lex->type))
        {
            lex = lex->next; // Skip the next node of the redirection
        }
        lex = lex->next;
    }
    args[i] = NULL;
    return (args);
}

void handler_things(t_parser *p, t_lexer **lex, t_redir *r)
{
    t_parser *pars;
    t_redir *red;

    pars = p;
    red = r;
    while (*lex)
    {
        if ((*lex)->type == CMD)
        {
            parser_lstadd_back(&pars, new_parser_node(cmd(*lex)));
            pars = pars->next;
            while (*lex && (*lex)->type != PIPE && !is_redir((*lex)->type))
            {
                (*lex) = (*lex)->next;
            }
        }
        else if (is_redir((*lex)->type))
        {
            redir_lstadd_back(&red, create_redir_node((*lex)->next->str, (*lex)->type));
            red = red->next;
            if ((*lex)->next)
                (*lex)->next->type = (*lex)->type; // change the type of the next token
            *lex = (*lex)->next->next;
        }
        else
        {
            (*lex) = (*lex)->next;
        }
    }
    if ((*lex) && (*lex)->type == PIPE)
    {
        redir_lstadd_back(&red, create_redir_node(NULL, PIPE));
        red = red->next;
        (*lex) = (*lex)->next;
    }
    red = NULL;
    pars = NULL;
}

void parser(t_mch *sh, t_lexer *lex)
{
    t_parser *p_tmp;
    t_redir *redir;
    int i;
    int pipes;

    i = 0;
    redir = ft_calloc(sizeof(t_redir) + 1, 1);
    pipes = count_pipes(lex);
    p_tmp = NULL;
    p_tmp = ft_calloc(sizeof(t_parser),  pipes + 2);
    p_tmp->args = (char **)ft_calloc((count_words(lex) + 2), sizeof(char *));
    while (i < pipes)
    {
        handler_things(p_tmp, &lex, redir);
        i++;
    }
    sh->red = redir;
    sh->parser = p_tmp;
    //mafree(p_tmp);
    //free_tab(p_tmp->args);
}
