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
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/include/libft.h"
# include <sys/stat.h>

#ifdef __linux__
# include "tcl/tcl.h"
#elif defined(__APPLE__) || defined(__MACH__)
# include <tcl.h>
#endif

# define EMPTY 0
# define CMD 1
//# define ARG 2
# define APPEND 3
# define TRUNC 4
# define PIPE 5
# define INPUT 6
# define HERE_DOC 7
# define END 8
# define REDIR 9
# define WORD 10
# define SCUOTE 39
# define DCUOTE 34

typedef struct s_arg
{
	char			*arg;
	struct s_arg	*next;
}	t_arg;

typedef struct s_redir
{
	//if -1 redir from/to file
	t_arg			*arg;
	int				fd;
	int				type;
	struct s_redir	*next;
    int   	input;
    int		output;
	char	*file;
    int		permission;
}   t_redir;


typedef struct s_cmd
{
	char	**args;
	t_arg	*arg;
	t_arg	*arg_x;
	t_redir	*red;
	t_redir	*red_x;
}   t_cmd;

typedef struct s_clean
{
	bool	dcuote;
	bool	scuote;
	bool	space;
	char	*str;
}	t_clean;


typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char          **ms_env;
	char          *key;
	char          *value;
	int           capacity;
	struct s_env  *prev;
	struct s_env  *next;
}	t_env;


typedef struct s_mch
{
	t_cmd	**cmd;
	t_redir	*redir;
	t_token	*tok;
	char	**env;
	char	**arg;
	char	*old_pwd;
	char	*pwd;
	int		pipes;
}	t_mch;

// system/minishell.c
void	minishell(t_mch *sh, char **env);

// system
void	signals(void);
void 	sigint_handler(int sig);
void	prompter(void);
char	*shell_prompt(int i);

// builtins env
bool	bt_is_builtin(char **argv);
void	bt_check_builtin(char **argv, char **env);
void	bt_env(char **env);
void	bt_exit(char *argv);


// parser
void	get_env(char **env);
void	symbol_sorter(t_token *tok);
void	parser(t_mch *sh, t_token *tok);

int		syntax_checker(char *line);
void	syntax_error(void);
int		pwd(void);
void	bt_echo(t_token *tok);
//int		bt_get_dirs(char **env, t_env *env_routes);
//int		bt_cd(char *input, t_env env_routes);

//ESTRUCTURA TOKEN CON ARGV, ARGC Y TIPO QUE PUEDE SER COMANDO O SEPARADOR
//DEJAR EN ARGV LAS COMILLAS DOBLES 
//STRJOINCHAR PARA IR PONIENDO LOS CARÁCTERES AL LINE LIMPIO
//ENTERO COMILLAS PARA QUE SI ESTÁN ACTIVAS SE PASE DE LOS ESPACIOS
//SI HAY COMILLA ENTRE COMILLAS SE IGNORA Y SI HAY COMILLAS ENTRE COMILLA SE IGNORA

// Utils.c
char	*charjoin(char *s1, char c);
char	*ft_strndup(const char *src, size_t len);
int		ft_isquote(int c);
int		ft_is_escape(int c);
int		ft_is_shellsymbol(int c);
void	print_tokens(t_token *tok, char *str);
char	**split_cmd(char *cmd, int quotes);
int		count_quotes(char *cmd);

//utils list
t_token	*lexer_lstnew(void);
void	lexer_lstadd_back(t_token **lst, t_token *new);
t_arg	*argnew(void *content);
t_arg	*arglast(t_arg *lst);
void	argback(t_arg **lst, t_arg *new);
int		argsize(t_arg *lst);
void	argfront(t_arg **lst, t_arg *new);
void	argclear(t_arg **lst);
t_redir	*redirnew(int type);
void	redirback(t_redir **lst, t_redir *new);
t_redir	*redirlast(t_redir *lst);
void	redclear(t_redir **lst);

char	*clean_input(char *line);
int		next_alloc(char *line, int i);
t_token	*next_token(char *line, int *i);
int		main_lexer(char *str, t_token **tok);

#endif // !MINISHELL_H
