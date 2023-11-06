#include "../../inc/minishell.h"

void	syntax_error(void)
{
	ft_printf(STDERR_FILENO, "minishell: Invalid Syntax not closed quotes\n");
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

int	quote_checker(char *line)
{
	char	*end_subshell;
	bool		dcuotes;
	bool		scuotes;
	int		parenthesis;

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
		++line;
		}
		if (parenthesis != 0 || dcuotes || scuotes)
			return (0);
	return (1);
}
