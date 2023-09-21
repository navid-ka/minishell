#include "../../inc/minishell.h"

int	ft_is_escape(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == SCUOTE || c == DCUOTE)
		return (1);
	return (0);
}

int	ft_is_shellsymbol(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	print_tokens(t_token *tok, char *str)
{
	printf("input: %s\n", str);
	while (tok)
	{
		if (tok->type != 0)
		{
			if (tok->type == PIPE)
				printf("PIPE\n");
			else if (tok->type == APPEND)
				printf("TRUNC\n");
			else if (tok->type == TRUNC)
				printf("APPEND\n");
			else if (tok->type == INPUT)
				printf("INPUT\n");
			else if (tok->type == HERE_DOC)
				printf("HERE_DOC\n");
		}
		else
			printf("%s\n", tok->str);
		tok = tok->next;
	}
	printf("\n");
}
