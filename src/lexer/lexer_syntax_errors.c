#include "../../inc/minishell.h"

void	syntax_error(void)
{
	ft_printf(STDERR_FILENO, "minishell: Invalid Syntax at token\n");
}

char	*lexer_end_subshell(char *line)
{
	if (!line)
		return (NULL);
	while (*line)
	{
		if (*line == '&')
			return (line);
		if (*line == '|')
			return (line);
		if (*line == '<')
			return (line);
		if (*line == '>')
			return (line);
		++line;
	}
	return (line);
}

/*
Además, los caracteres siguientes y caracteres dobles también forman palabras simples cuando se utilizan como separadores de mandatos o terminadores:
&       |      ;        
&&      ||    <<        > >
<       >     (          )
*/

//si hago "   '   " debería ser correcto

int	syntax_checker(char *line) //falta adaptarlo para que revise todos los subshells
{
	int		i;
	char	*end_subshell;
	bool		dcuotes;
	bool		scuotes;
	int		parenthesis;

	i = 0;
	parenthesis = 0;
	dcuotes = false;
	scuotes = false;
	end_subshell = lexer_end_subshell(line);
	while (line != end_subshell)
	{
		if (*line == '(')
			parenthesis++;
		else if (*line == ')')
			parenthesis--;
		else if (*line == '"' && !scuotes)
			dcuotes = !dcuotes;
		else if (*line == '\'' && !dcuotes)
			scuotes = !scuotes;
		if (parenthesis < 0)
			return (0);
		if (*line == '\\' || *line == ';')
			return (0);
		++line;
	}
	if (parenthesis != 0 || dcuotes | scuotes)
		return (0);
	return (1);
}
