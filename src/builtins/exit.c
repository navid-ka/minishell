#include "../../inc/minishell.h"

void	bt_exit(char *argv)
{
  if (!argv)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
}
