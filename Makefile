MAKEFLAGS 		+= --no-print-directory
UNAME					:= $(shell uname)
NAME					:= minishell
LIB_DIR				:= libs/

LIBFT					:=	$(LIB_DIR)libft/
RDLINE				:=	$(LIB_DIR)readline/

SRC_DIR				:=	src/
OBJ_DIR				:=	objs/
INC_DIR				:=	inc/

LIBS				 	:= $(RDLINE)libreadline.a $(RDLINE)libhistory.a \
									$(LIBFT)bin/libft.a
ifeq ($(UNAME), Linux)
	LIBS_LINK			:= -L$(RDLINE) -L$(LIBFT) -lreadline -lhistory -lncurses
else
	LIBS_LINK			:= -L$(RDLINE) -L$(LIBFT) -lreadline -lhistory -ltermcap
endif

HEADERS				:= $(INC_DIR) $(LIBFT)include/ $(RDLINE)


SRCS 					:= src/main.c src/builtins/env.c src/lexer/lexer_syntax_errors.c src/builtins/pwd.c  src/builtins/cd.c \
								 src/utils/utils.c src/lexer/lexer.c

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

CFLAGS 				:= -Wall -Wextra -Werror
DFLAGS				:= -MMD -MF
INCLUDE				:= -I $(INC_DIR) -I $(LIBFT)include/ -I $(RDLINE)

all:
		$(MAKE) -C $(LIBFT)
		$(MAKE) -C $(RDLINE)
		$(MAKE) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBS)
	@printf "\rCompiling (╮°-°)╮┳━┳ : $<"
	mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJS) $(HEADERS) Makefile $(LIBS)
	mkdir -p $(@D)
	gcc $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_LINK) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(RDLINE) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
