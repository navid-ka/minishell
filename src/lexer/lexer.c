#include "../../inc/minishell.h"

void	clean_init(t_clean *cleaner) //pasarlo otro archivo de inits
{
	cleaner->dcuote = false;
	cleaner->scuote = false;
	cleaner->space = false;
	cleaner->str = NULL;
}

void	clean_quotes(char **line, t_clean *cleaner)
{
	if (cleaner->dcuote)
	{
		while (**line && **line != '\"')
		{
			cleaner->str = charjoin(cleaner->str, **line);
			(*line)++;
		}
		cleaner->str = charjoin(cleaner->str, **line);
		cleaner->dcuote = false;
		(*line)++;
	}
	else
	{
		while (**line && **line != '\'')
		{
			cleaner->str = charjoin(cleaner->str, **line);
			(*line)++;
		}
		cleaner->str = charjoin(cleaner->str, **line);
		cleaner->scuote = false;
		(*line)++;
	}
}

void	clean_spaces(char **line, t_clean *cleaner)
{
	if (**line == ' ' && !(cleaner->space))
	{
		cleaner->space = true;
		cleaner->str = charjoin(cleaner->str, **line);
	}
	if (**line != ' ')
	{
		cleaner->space = false;
		cleaner->str = charjoin(cleaner->str, **line);
	}
	if (**line == '\"')
		cleaner->dcuote = true;
	else if (**line == '\'')
		cleaner->scuote = true;
	++(*line);
}

char	*clean_input(char *line)
{
	t_clean	cleaner;

	clean_init(&cleaner);
	while (*line)
	{
		if (!(cleaner.dcuote) && !(cleaner.scuote))
			clean_spaces(&line, &cleaner);
		else
			clean_quotes(&line, &cleaner);
	}
	return (cleaner.str);
}
