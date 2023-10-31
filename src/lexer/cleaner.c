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
		while (**line && **line != DCUOTE)
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
		while (**line && **line != SCUOTE)
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
	//mirar c == ' ' || c == '\n' || c == '\t' || c == '\v' 
	//|| c == '\f' || c == '\r')
	if (ft_is_escape(**line) && !(cleaner->space))
	{
		cleaner->space = true;
		cleaner->str = charjoin(cleaner->str, **line);
	}
	if (!ft_is_escape(**line))
	{
		cleaner->space = false;
		cleaner->str = charjoin(cleaner->str, **line);
	}
	if (**line == DCUOTE)
		cleaner->dcuote = true;
	else if (**line == SCUOTE)
		cleaner->scuote = true;
	++(*line);
}

char	*clean_input(char *line)
{
	t_clean	cleaner;
	char	*output;

	clean_init(&cleaner);
	while (*line)
	{
		if (!(cleaner.dcuote) && !(cleaner.scuote))
			clean_spaces(&line, &cleaner);
		else
			clean_quotes(&line, &cleaner);
	}
	output = cleaner.str;
	//clear_line(&cleaner.str);
	return (output);
}
