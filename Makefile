MAKEFLAGS 		+= --no-print-directory
UNAME					:= $(shell uname)
NAME					:= minishell
LIB_DIR				:= libs/

LIBFT					:=	$(LIB_DIR)libft/

SRC_DIR				:=	src/
OBJ_DIR				:=	objs/
INC_DIR				:=	inc/
ifeq ($(UNAME), Darwin)
	LIBS				 	:= $(LIBFT)bin/libft.a
	LIBS_LINK			:= -L$(LIBFT) -L${HOME}/.brew/opt/readline/lib -lreadline -lhistory -ltermcap
	HEADERS				:= $(INC_DIR) $(LIBFT)include/ 
	INCLUDE				:= -I $(INC_DIR) -I $(LIBFT)include/ -I${HOME}/.brew/opt/readline/include
else
	LIBS				 	:= $(LIBFT)bin/libft.a
	LIBS_LINK			:= -L$(LIBFT) -lreadline -lhistory -ltermcap
	HEADERS				:= $(INC_DIR) $(LIBFT)include/ 
	INCLUDE				:= -I $(INC_DIR) -I $(LIBFT)include/
endif

SRCS 					:= src/main.c  \
						src/builtins/env.c \
						src/lexer/lexer_syntax_errors.c \
						src/builtins/pwd.c \
						src/builtins/cd.c \
						src/builtins/echo.c \
						src/builtins/exit.c \
						src/builtins/export_utils.c \
						src/builtins/export.c \
						src/builtins/unset.c \
						src/utils/utils.c \
						src/system/signals.c \
						src/system/prompter.c \
						src/system/minishell.c \
						src/lexer/real_lexer.c \
						src/lexer/lexer_utils.c \
						src/lexer/lexer_list.c \
						src/lexer/cleaner.c \
						src/parser/parser.c \
						src/parser/parse_list.c \
						src/parser/parse_utils.c \
						src/parser/redir_list.c \
						src/builtins/bt_init.c \
						src/parser/parse_env.c \
						src/expander/expansor_utils.c \
						src/expander/expand_types.c \
						src/expander/expansor.c \
						src/executor/executor.c \
						src/executor/childs.c \
						src/executor/exec_errors.c \
						src/executor/exec_utils.c \
						src/executor/redirs.c \
						src/utils/garbage_collector.c  \
						src/utils/garbage_collector2.c  \
						src/lexer/syntax_errors.c 	\
						src/builtins/exit_utils.c  \
						src/executor/here_doc.c


OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
CFLAGS 				:= -g -Wall -Wextra -Werror

LINUX_DISTRIBUTION := $(shell lsb_release -si)
ifeq ($(LINUX_DISTRIBUTION),EndeavourOS)
	CFLAGS 				+= -D ARCHBTW
endif

all:
		@$(MAKE) -C $(LIBFT)
		@$(MAKE) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBS)
	@printf "\rCompiling (╮°-°)╮┳━┳ : $<"
	@mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJS) $(HEADERS) Makefile $(LIBS)
	@mkdir -p $(@D)
	gcc $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_LINK) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -rf $(NAME) minishell.dSYM/

re: fclean all

.PHONY : all clean fclean re
