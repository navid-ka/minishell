#include "minishell.h"

int	is_redir(t_lexer *tok)
{
	if (tok && (tok->type == TRUNC || tok->type == APPEND \
		|| tok->type == HERE_DOC || tok->type == INPUT))
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
	while (first && first->type != PIPE)
	{
		words++;
		first = first->next;
	}
	return (words);
}

char	**handle_command(t_lexer *lex)
{
    char **args;
	int	i;
    t_lexer *current_lexer = lex;

	i = 0;
	args = (char **)ft_calloc((count_words(current_lexer) + 2), \
			sizeof(char *)); //revisar +2
	while (current_lexer && current_lexer->type != PIPE)
	{
        if (is_redir(current_lexer))
            current_lexer = current_lexer->next;
		args[i] = ft_strdup(current_lexer->str);
		i++;
		current_lexer = current_lexer->next;
	}
	args[i] = NULL;
    return (args);
}

t_redir    *handle_redirs(t_lexer *current_lexer)
{
    t_redir *act;

    act = NULL;
    while (current_lexer && current_lexer->type != PIPE)
    {
        if (is_redir(current_lexer)) {
            act->file = current_lexer->next->str;
            act->type = current_lexer ->type;  
            current_lexer = current_lexer->next;      
        }
        current_lexer = current_lexer->next;      
    }
    return (act);
}


void parser(t_mch *sh, t_lexer *lex)
{
    t_parser *pars;
    t_parser *p_tmp;
    t_redir *redir;
    int i;

    i = 0;
    pars = malloc(sizeof(t_parser) * 5);
    p_tmp = pars;
    p_tmp->args = (char **)ft_calloc((count_words(lex) + 2), \
			sizeof(char *));
    int pipes = count_pipes(lex);
    while (i < pipes && lex)
    {
        p_tmp->args = handle_command(lex);
        p_tmp = p_tmp->next;
        redir = handle_redirs(lex);
        i++;
    }
    p_tmp = NULL;
    sh->parser = pars;
    //redir[i] = NULL;
}

// while tok
// if tok && tok->type != 
//     handle
// else 
//     addback(reder, handle_redirs(lex))