#include "../../inc/minishell.h"

void	clean_spaces(char **line)
{
	bool	dcuote;
	bool	scuote;
	char	str;

	dcuote = false;
	scuote = false;
	while (**line)
	{
		if (!dcuote && !scuote)
		{
			if (**line != ' ')
				ft_strjoinchr(str, **line);
			if (**line == '"')
				!dcuote;
			else if (**line == '\'')
				!scuote;
			++(*line);
		}
		else {
			if (dcuote)
			{
				while (**line != '\"')
					{
						ft_strjoinchr(str, **line);
						*line++;
					}
				!dcuote;
			}
			else
			{
				while (**line != '\'')
				{
					ft_strjoinchr(str, **line);
					*line++;
				}
				!scuote;
			}
		}
	}
}
