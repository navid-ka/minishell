#include "../../inc/minishell.h"

int sg_init(int sig)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
