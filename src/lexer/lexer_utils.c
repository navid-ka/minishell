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

void 	print_lex_list(t_lexer *lex)
{
	t_lexer	*ptr;

	ptr = lex;
	while(ptr)
	{
		//printf("%s\n", ptr->str);
		printf("type %d:\n", ptr->type);
		ptr = ptr->next;
	}
}

void	print_lexers(t_lexer *lex, char *str)
{
	printf("input: %s\n", str);
	t_lexer	*ptr;

	ptr = lex;
	while (ptr)
	{
		if (ptr->type != 0)
		{
			if (ptr->type == PIPE)
				printf("PIPE\n");
			else if (ptr->type == APPEND)
				printf("TRUNC\n");
			else if (ptr->type == TRUNC)
				printf("APPEND\n");
			else if (ptr->type == INPUT)
				printf("INPUT\n");
			else if (ptr->type == HERE_DOC)
				printf("HERE_DOC\n");
		}
		else
			printf("%s\n", ptr->str);
		ptr = ptr->next;
	}
	printf("\n");
}
