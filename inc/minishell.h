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

// PARSER
# define EMPTY 0 
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
# define EXPORT "export %s=%s: not a valid identifier\n"

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
}	t_redir;

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
	char	**args;
	t_redir	red;
	int num_cmds;
	struct s_parser *next;
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
void		minishell(t_mch *sh, char **env);

// system
void		signals(void);
void 		sigint_handler(int sig);
void		prompter(void);
char		*shell_prompt(int i);

// Garbage collection 
void		clear_parser(t_parser **lst);
void		clear_lexer(t_lexer **lexer_list);
void		free_tab(char **args);
void		clear_line(char **line);
void		free_env(t_env **env);
void		unset_free(t_env *env);

// builtins env
bool		bt_is_builtin(char **argv);
void		bt_check_builtin(t_mch *sh);
void		bt_env(t_mch *sh);
void		bt_export(t_mch *sh, char **args);
void		bt_exit(t_mch *sh, char *argv);
void		bt_echo(t_mch *sh, char **str);
int			bt_pwd(void);
void		bt_cd(t_mch *sh, char **arg);
void 		bt_unset(t_mch *sh, char **args);

// parser
void		get_env(t_mch *sh, char **env);
t_parser	*convert_lexer_parser(t_lexer *lexerList);
void		printparser_list(t_parser *parser_list);
int			quote_checker(char *line);
void		syntax_error(void);

int check_syntax(t_lexer *tok); // new

// Utils.c
char		*charjoin(char *s1, char c);
char		*ft_strndup(const char *src, size_t len);
int			ft_isquote(int c);
int			ft_is_escape(int c);
int			ft_is_shellsymbol(int c);
void		add_or_update_env(t_mch *sh, char *name, char *value);
char		*get_env_value(t_mch *sh, char *arg);

void		print_lexers(t_lexer *lex, char *str);
int			count_quotes(char *cmd);
char		*find_in_env_variables(t_mch *sh, char *variable_name);

//utils list

t_lexer		*lexer_lstnew(void);
void		lexer_lstadd_back(t_lexer **lst, t_lexer *new);
char		*clean_input(char *line);
void		free_tab(char **args);
int			main_lexer(char *str, t_lexer **lex);
void		add_env_to_list(t_env **env, t_env *new_env);
void		print_lex_list(t_lexer *lex);

// expansor
int			is_expandable(char e);
void		init_quotes(t_clean *quotes);
void		quote_updater(t_clean *quotes, char e);
void		expansor(t_mch *sh);
void		print_expansor(t_mch *sh);

// executor
void		executor(t_mch *sh);
char		*find_cmd(char **routes, char *cmd);
void		last_pipe(t_pipe *pipex, int argc);
int			ft_error(int ext, int err, char *cmd);
void		close_pipes(t_pipe *pipex);

#endif
