MAKEFLAGS += --no-print-directory

NAME					:= minishell
LIB_DIR				:= libs/

LIBFT					:=	$(LIB_DIR)libft/
RDLINE				:=	$(LIB_DIR)readline/

SRC_DIR				:=	src/
OBJ_DIR				:=	.objs/
INC_DIR				:=	inc/

LIBS				 	:= $(RDLINE)libreadline.a $(RDLINE)libhistory.a \
									$(LIBFT)bin/libft.a
LIBS_LINK			:= -L$(RDLINE) -L$(LIBFT) -lreadline -lhistory
								 

HEADERS				:= $(INC_DIR) $(LIBFT)include/ $(RDLINE)

SRCS 					:= src/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CFLAGS 				:= -Wall -Wextra -Werror
DFLAGS				:= -MMD -MF
INCLUDE				:= -I$(HEADERS)

all:
		$(MAKE) -C $(LIBFT)
		$(MAKE) -C $(RDLINE)
		$(MAKE) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBS) | $(call create_dir,$(OBJ_DIR))
	@printf "\rCompiling (╮°-°)╮┳━┳ : $<"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJS) $(HEADERS) Makefile
	@gcc $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_LINK) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(RDLINE) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(RDLINE) clean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re

