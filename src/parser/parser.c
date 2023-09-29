#include "minishell.h"

//comando < archivo_de_entrada
//comando > archivo_de_salida
//comando >> archivo_de_salida
//comando << DELIMITADOR

int count_args(t_lexer *lex) {
	t_lex *act = *lex;
	int args = 0;

	while (lex->next) {
		if (lex->type = 0) args++;
		if (ft_is_shellsymbol(lex->next->type)) return (args);
	}
	return (args);
}

//void cmd_compactor()

//FALTA HERE_DOC

t_lex	*make_lexer_parsed(t_lex *original) {
	t_lex *new;
	t_lex *act;

	while (original) {
		if (ft_is_shellsymbol(original->type)) {
			act = lexer_lstnew();
			if (original->type == INPUT) {
				act->redir.file = act->next->str;
				act->redir.input = INPUT;
			}
			if (original->type == TRUNC || original->type == APPEND) {
				act->redir.file = act->next->str;
				act->redir.output = original->type;
			}
			if (original->type == PIPE && !ft_is_shellsymbol(original->next->type)) {
				act->redir.infile = 
			}
		} 
	}

}

//hacer dibujo para interpretarlo mejor