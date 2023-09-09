#include "../../inc/minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		perror("Error");
		return (0);
	}
	if (ft_printf(2, "%s\n", pwd) == -1)
		return (0);
	free(pwd);
	return (1);
}