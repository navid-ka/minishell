#include "minishell.h"

void	arg_type(t_token *token)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= APPEND)
		token->type = CMD;
	else
		token->type = ARG;
}

int		next_alloc(char *line, int i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[i + j] && (line[i + j] != ' ' || c != ' ')) //si hay linea, no encuentra espacio o la comilla es delimitador sigue
	{
		if (c == ' ' && (line[i + j] == '\'' || line[i + j] == '\"')) //primera comilla
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
	return (j - count + 1);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * next_alloc(line, *i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
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
		arg_type(next);
		line++;
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

//si es <infile no funciona porque no lo separa
//infile outfile los detecta como comandos