#include "minishell.h"

void	arg_type(char *str, int i, t_token *token)
{
	token->type = 0;
	if (str[i] == '|')
		token->type = PIPE;
	else if (str[i] == '<' && str[i + 1] == '<')
		token->type = APPEND;
	else if (str[i] == '<')
		token->type = TRUNC;
	else if (str[i] == '>' && str[i + 1] == '>')
		token->type = HERE_DOC;
	else if (str[i] == '>')
		token->type = INPUT;
}


int		next_alloc(char *line, int i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	if (line[i + j] == '|' || line[i + j] == '>' || line[i + j] == '<')
		return (0); //para que no asigne memoria
	while (line[i + j] && (line[i + j] != ' ' || c != ' ')) //si hay linea, no encuentra espacio o la comilla es delimitador sigue
	{
		if (c == ' ' && (line[i + j] == S_QUOTE || line[i + j] == D_QUOTE)) //primera comilla
			c = line[i + j++];
		else if (c != ' ' && line[i + j] == c) //segunda comilla
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++; //ves avanzando
		if (line[i + j - 1] == '\\')
			count--;
	}
	//printf("\n\n%d\n\n", count);
	return (j + count);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		token = malloc(sizeof(t_token));
		// printf("%d\n\n", next_alloc(line, *i));
		token->str = ft_substr(line, *i, next_alloc(line, *i)); //si len es 0 return NULL
		arg_type(line, *i, token);
		//printf("%c\n", line[*i]);
		printf("%s\n\n", token->str);
		*i += next_alloc(line, *i) + 1;
		printf("%d\n\n", *i);
	}
	token->str[j] = '\0';
	return (token);
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	t_token *first;
	int		i;

	prev = NULL;
	next = NULL;
	first = NULL;
	i = 0;
	while (line[i])
	{
		next = next_token(line, &i);
		if (!first)
			first = next;
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		line += i - 1;
	}
	if (next)
		next->next = NULL;
	return (first);
}

t_token *prev_command(t_token *token)
{
	while (token->prev && token->prev->type < APPEND)
		token = token->prev;
	return (token);
}

//hacer split de argumentos para el execve

//si es <infile no funciona porque no lo separa
//infile outfile los detecta como comandos


//FOTO JARESTE MEJOR CARGARME SIMBOLOS Y NOMBRAR COSAS COMO LA REDIRECCIÓN A LA QUE PERTENECEN 
//ARGUMENTOS SON TIPO 0 COMO COMANDOS Y >| ME CARGO PIPES PORQUE ESTÁN DEBAJO EN JERARQUIA