#include "../../inc/minishell.h"

char	*clean_spaces(char *line)
{
	bool	dcuote;
	bool	scuote;
	bool	space;
	char	*str;

	dcuote = false;
	scuote = false;
	space = false;
	str = NULL;
	while (*line)
	{
		//printf("%d\n", dcuote);
		if (!dcuote && !scuote)
		{
			if (*line == ' ' && !space)
			{
				space = true;
				str = charjoin(str, *line);
			}
			if (*line != ' ')
			{
				space = false;
				str = charjoin(str, *line);
			}
			if (*line == '\"')
				dcuote = true;
			else if (*line == '\'')
				scuote = true;
			++line;
		}
		else {
			if (dcuote)
			{
				while (*line && *line != '\"')
				{
					str = charjoin(str, *line);
					line++;
				}
				str = charjoin(str, *line);
				dcuote = false;
				line++;
			}
			else
			{
				while (*line && *line != '\'')
				{
					str = charjoin(str, *line);
					line++;
				}
				str = charjoin(str, *line);
				scuote = false;
				line++;
			}
		}
	}
	return (str);
}

//si hay comillas se lia y error de comillas sin cerrar falla si hay comilla suelta dentro de comillas