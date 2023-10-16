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
# include <fcntl.h>

#ifndef __linux__
# include "tcl/tcl.h"
#endif

#if defined(__APPLE__) || defined(__MACH__)
# include <tcl.h>
#endif

#ifdef ARCHBTW
# include <tcl.h>
#endif


//PIPEX
# define ERR_ARG	1
# define ERR_MC		2
# define ERR_CNF	300
# define ERR_PERM	400
# define ERR_NFD	500
# define ERR_PERR	1000
/*
typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		permission;
	char	**routes;
	pid_t	proc;
	int		tube[2];
	char	**cmd_args;
	char	*cmd;
	int		j;
	int		here_doc;
	char	*limiter;
}	t_pipe;*/

//PIPEXFIN
# define EMPTY 0 
//# define ARG 2
# define APPEND 3
# define TRUNC 4
# define PIPE 5
# define INPUT 6
# define HERE_DOC 7
# define END 8
# define REDIR 9
# define CMD 10
# define SCUOTE 39
# define DCUOTE 34

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
    int   	input;
    int		output;
	char	*infile;
	char	*outfile;
	//int		fd;
	// struct s_redir *next;

    //int		permission; and more
}   t_redir;

typedef struct s_clean
{
	bool	dcuote;
	bool	scuote;
	bool	space;
	char	*str;
}	t_clean;


typedef struct s_lexer
{
	char			*str;
	int				type;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_parser
{
	//char	*cmd;
	char	**args;
	t_redir	red;
	int num_cmds; //no he probado este argc
	struct s_parser *next;
	//seguramente ponga struct s_parser *prev
}	t_parser;

typedef struct s_pipe
{
	int		fd_infile;
	int		fd_outfile;
	int		permission;
	char	**routes;
	pid_t	proc;
	int		tube[2];
	int		j;
	int		here_doc;
	char	*limiter;
}	t_pipe;

typedef struct s_mch
{
	t_parser *parser;
	t_lexer	*lex;
	t_pipe	*pipex;
	t_env	*env;
	char	*old_pwd;
	char	*pwd;
	int		exit;
}	t_mch;



// system/minishell.c
void	minishell(t_mch *sh, char **env);

// system
void	signals(void);
void 	sigint_handler(int sig);
void	prompter(void);
char	*shell_prompt(int i);

// Garbage collection 
void	clear_parser(t_parser **lst);
void	clear_lexer(t_lexer **lexer_list);
void	free_tab(char **args);
void	clear_line(char **line);
void	free_env(t_env **env);
void	unset_free(t_env *env);

// builtins env
bool	bt_is_builtin(char **argv);
void	bt_check_builtin(t_mch *sh);
void	bt_env(t_mch *sh);
void	bt_export(t_mch *sh, char **args);
void	bt_exit(char *argv);
void	bt_echo(t_mch *sh);
int		bt_pwd(void);
void	bt_cd(t_mch *sh, char **arg);
void    bt_unset(t_mch *sh, char **args);

// parser
void	get_env(t_mch *sh, char **env);
void	symbol_sorter(t_lexer *lex);
void	parser(t_mch *sh, t_lexer *lex);
t_parser *convertLexerToParser(t_lexer *lexerList);
void printParserList(t_parser *parserList);

int		syntax_checker(char *line);
void	syntax_error(void);


//int		bt_get_dirs(char **env, t_env *env_routes);
//int		bt_cd(char *input, t_env env_routes);

//ESTRUCTURA lexer CON ARGV, ARGC Y TIPO QUE PUEDE SER COMANDO O SEPARADOR
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
void	add_or_update_env(t_mch *sh, char *name, char *value);

void	print_lexers(t_lexer *lex, char *str);

char	**split_cmd(char *cmd, int quotes);
int		count_quotes(char *cmd);
char	*find_in_env_variables(t_mch *sh, char *variable_name);

//utils list

t_lexer	*lexer_lstnew(void);
void	lexer_lstadd_back(t_lexer **lst, t_lexer *new);
char	*clean_input(char *line);
void	free_tab(char **args);
int		main_lexer(char *str, t_lexer **lex);
void	add_env_to_list(t_env **env, t_env *new_env);


void 	print_lex_list(t_lexer *lex);
void 	print_pars_list(t_parser *lex);

// expansor
int	is_expandable(char e);
void	init_quotes(t_clean *quotes);
void	quote_updater(t_clean *quotes, char e);
void	expansor(t_mch *sh);
void	print_expansor(t_mch *sh);

// executor
void	executor(t_mch *sh);

// pipes
void	init_pipex(t_pipe *pipex, char **envp);
int		find_route(t_pipe *pipex, char **envp);
char	*find_path(char **envp, int *found);
char	*find_cmd(char **routes, char *cmd);
int		wait_forks(t_pipe *pipex);
void	last_pipe(t_pipe *pipex, int argc);
int		ft_error(int ext, int err, char *cmd);
void	close_pipes(t_pipe *pipex);


#endif // !MINISHELL_H
