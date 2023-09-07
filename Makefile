MAKEFLAGS += --no-print-directory

NAME					:= minishell
LIB_DIR				:= libs/

LIBFT					:=	$(LIB_DIR)libft/
RDLINE				:=	$(LIB_DIR)readline/

SRC_DIR				:=	src/
OBJ_DIR				:=	.objs/
DEP_DIR				:=	.deps/
INC_DIR				:=	inc/

LIBS				 	:= $(RDLINE)libreadline.a $(RDLINE)libhistory.a \
									$(LIBFT)bin/libft.a
LIBS_LINK			:= -L$(RDLINE) -L$(LIBFT)
LIBS_LINKER		:= -lreadline -lhistory -ltermcap -lft

HEADERS				:= $(INC_DIR) $(LIBFT)include/ $(RDLINE)

vpath %.c $(SRC_DIR)

SRCS 					:= main.c
OBJS					:=	$(addprefix $(OBJ_DIR),$(subst .c,.o,$(SRCS)))
DEPS					:=	$(addprefix $(DEP_DIR),$(subst .c,.d,$(SRCS)))

CFLAGS 				:= -Wall -Wextra -Werror
INCLUDE				:= -I$(HEADERS)

