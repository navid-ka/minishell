#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <tcl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/include/libft.h"
# include <sys/stat.h>

typedef struct s_pipe
{
	char	**routes;
	pid_t	proc;
    int		tube[2];
	char	**cmd_args;
	char	*cmd;
	int		j; //para jugar con posición tratada en cada momento
	int		here_doc; //booleano por si entra un >> limiter
	char	*limiter; //por >>
}	t_pipe;

typedef struct s_cmd
{
    int     infile;
    int		outfile;
    int		permission; //solo para jugar con access
}   t_cmd;

#endif // !MINISHELL_H
