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

typedef struct s_env
{
	char	*home;
	char	*oldpwd;
}	t_env;

void	bt_env(char **env);
int		syntax_checker(char *line);
void	syntax_error(void);
int		pwd(void);
int		bt_get_dirs(char **env, t_env *env_routes);
//int		bt_cd(char *input, t_env env_routes);

//ESTRUCTURA TOKEN CON ARGV, ARGC Y TIPO QUE PUEDE SER COMANDO O SEPARADOR
//DEJAR EN ARGV LAS COMILLAS DOBLES 
//STRJOINCHAR PARA IR PONIENDO LOS CARÁCTERES AL LINE LIMPIO
//ENTERO COMILLAS PARA QUE SI ESTÁN ACTIVAS SE PASE DE LOS ESPACIOS
//SI HAY COMILLA ENTRE COMILLAS SE IGNORA Y SI HAY COMILLAS ENTRE COMILLA SE IGNORA


#endif // !MINISHELL_H
