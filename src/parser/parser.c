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
	while (first && first->type != PIPE)
	{
		words++;
		first = first->next;
	}
	return (words);
}

// char	**handle_command(t_lexer *lex, t_redir *red)
// {
//     char **args;
// 	int	i;
//     t_lexer *current_lexer;
//     t_redir *act;
//     current_lexer = lex;
//     act = red;

// 	i = 0;
// 	args = (char **)ft_calloc((count_words(current_lexer) + 2), \
// 			sizeof(char *)); revisar +2
// 	while (current_lexer && current_lexer->type != PIPE)
// 	{
//         while (current_lexer && is_redir(current_lexer))
//         {
//             handle_redirs(current_lexer);
//             current_lexer = current_lexer->next->next;
//         }
// 		args[i] = ft_strdup(current_lexer->str);
// 		i++;
// 		current_lexer = current_lexer->next;
// 	}
// 	args[i] = NULL;

//     return (args);
// }

// t_redir    *handle_redirs(char *file, int type)
// {
//     t_redir *act;

//     act = create_redir_node(file, type);
//     return (act);
// }

// char *cmd(char *str)
// {
//     char *arg;

//     arg = ft_strdup(str);
//     return (arg);
// }

void handler_things(t_parser *p, t_lexer **lex, t_redir *r) //p y r tienen malloc!
{
    t_parser *pars;
    t_redir *red;
    int i;
    
    i = 0;
    pars = p;
    red = r;
    while (*lex && (*lex)->type != PIPE)
    {
        if ((*lex)->type == CMD)
           pars->args[i++] = ft_strdup((*lex)->str);
        else if (is_redir((*lex)->type))
        {
            printf("type: %d\n", (*lex)->type);
            printf("out: %s\n", (*lex)->next->str);
            redir_lstadd_back(&red, create_redir_node((*lex)->next->str, (*lex)->type));
            red = red->next;
            *lex = (*lex)->next;
        }
        *lex = (*lex)->next;
    }
    if ((*lex) && (*lex)->type == PIPE)
    {
        redir_lstadd_back(&red, create_redir_node(NULL, PIPE));
        red = red->next;
        (*lex) = (*lex)->next;
    }
    red = NULL;
    pars->args[i] = NULL;
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
    sh->parser = ft_calloc(sizeof(t_parser),  pipes + 2); //esto seria 1 segun javi
    p_tmp = sh->parser;
    p_tmp->args = (char **)ft_calloc((count_words(lex) + 2), \
			sizeof(char *));
    while (lex && i < pipes)
    {
        printf("hay pipe\n");
        handler_things(p_tmp, &lex, redir);
         printf("seguro?\n");
        p_tmp = p_tmp->next;
        printf("muy seguro?\n");
        i++;
    }
    p_tmp = NULL;
    sh->red = redir;
    printparser_list(sh);
    //redir[i] = NULL;
}

// while tok
// if tok && tok->type != 
//     handle
// else 
//     addback(reder, handle_redirs(lex))