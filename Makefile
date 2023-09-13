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

SRCS 					:= src/main.c src/builtins/env.c src/lexer/lexer_syntax_errors.c src/builtins/pwd.c  src/builtins/cd.c \
								 src/utils/utils.c src/lexer/lexer.c src/signals/signals.c src/parser/parser.c \
							src/builtins/echo.c
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

CFLAGS 				:= -Wall -Wextra -Werror

all:
		@$(MAKE) -C $(LIBFT)
		@$(MAKE) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBS)
	@printf "\rCompiling (╮°-°)╮┳━┳ : $<"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJS) $(HEADERS) Makefile $(LIBS)
	@mkdir -p $(@D)
	@gcc $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_LINK) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
