#include "minishell.h"

void parser(t_mch *all) {
	t_parser *pars;
	all->parser = pars;

	t_parser *new = 
}

t_parser *create_node_parser(t_lexer *top_l) {
	int cmd = 0;
	int finish;
	t_lexer *lex = top_l;
	t_parser *top_p;
	t_parser *pars = top_p;

	if (lex->type = CMD) {
		if (pars != top_p) pars->red.input = pars->prev->red.output;
		pars->args = extract_cmd_args(lex);
		if (lex->next) pars->red.output = lex->next.type;
	}
	if (lex->type == INPUT) {
		pars->pars
	}
}

char **extract_cmd_args(t_lexer *lex) {
	char **cmd;
	int i = 0;
	while (lex->type == CMD) {
		cmd[i] = ft_strdup(lex->str);
		i++;
	}
	cmd[i] = NULL;
}