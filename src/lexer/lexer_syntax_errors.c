#include "../inc/minishell.h"

void	syntax_eror()
{
	ft_printf(STDERR_FILENO, "minishell: Invalid Syntax at token\n");
}

int	new_subshell(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '&')
		return (i);
	if (line[i] != '|')
		return (i);
	if (line[i] != '(')
		return (i);
}

/*
Además, los caracteres siguientes y caracteres dobles también forman palabras simples cuando se utilizan como separadores de mandatos o terminadores:
&       |      ;        
&&      ||    <<        > >
<       >     (          )*/

int	syntax_checker(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		//if ()
		if (*line == '\\' || *line == ';')
			return (0);
	}
}
