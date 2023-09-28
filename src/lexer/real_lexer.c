#include "../../inc/minishell.h"

//si falla llamar a función de liberar xd

void	arg_type(char *str, int *i, t_token *token)
{
	token->type = 0;
	if (str[*i] == '|')
		token->type = PIPE;
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		token->type = HERE_DOC;
		(*i)++;
	}
	else if (str[*i] == '<')
		token->type = INPUT;
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		token->type = APPEND;
		(*i)++;
	}
	else if (str[*i] == '>')
		token->type = TRUNC;
	(*i)++;
}

int cmd_type(char *str, int *i, t_token *new) {
	int		quoted;
	char	*cmd;
	int		j;

	quoted = 0;
	j = 0;
	while (str[*i + j])
	{
		if (quoted == 1 && ft_isquote(str[*i + j]) == 1)
			quoted = 0;
		else if (quoted == 0 && ft_isquote(str[*i + j]) == 1)
			quoted = 1;
		if (quoted == 0 && (ft_is_escape(str[*i + j])
				|| ft_is_shellsymbol(str[*i + j])))
			break ;
		j++;
	}
	cmd = ft_substr(str, *i, j);
	if (!cmd)
		return (-1);
	new->str = cmd;
	*i += j;
	return (0);
}

int	inicialize_tok(t_token **new, char *str, int *i) {
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
		arg_type(str, i, *new);
	else
		if (cmd_type(str, i, *new) == -1) return (-1);
	return (0);
}

int	main_lexer(char *str, t_token **tok) {
	t_token *new;
	int i = 0;
	while (str[i]) {
		if (str[i] != ' ') {
			new = lexer_lstnew();
			if (!new) return (-1);
			if (inicialize_tok(&new, str, &i) == -1) 
				return (-1);
			// dprintf(1, "%s, %d\n", new->str, new->type);
			lexer_lstadd_back(tok, new);
		}
		else i++;
	}
	return (0);
}

//hacer split de argumentos para el execve --> parser

//si es <infile no funciona porque no lo separa
//infile outfile los detecta como comandos


//FOTO JARESTE MEJOR CARGARME SIMBOLOS Y NOMBRAR COSAS COMO LA REDIRECCIÓN A LA QUE PERTENECEN 
//ARGUMENTOS SON TIPO 0 COMO COMANDOS Y >| ME CARGO PIPES PORQUE ESTÁN DEBAJO EN JERARQUIA
