############################		Variables		############################
include ../var.mk

NAME = ../$(VM_NAME)

LIB_DIR = ../libs
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes

LIBS = libft libftprintf libdraw

SRCS =	main.c				read_args.c			read_champion.c		\
		vm_core.c			vm_loop.c			vm_do_op.c			\
		carriage.c			memory.c			registers.c			\
		vm_args.c			op.c				print.c				\
		draw/core.c			draw/funcs.c		utils.c				\
		operations/live.c	operations/ld.c		operations/st.c		\
		operations/add.c	operations/sub.c	operations/and.c	\
		operations/or.c		operations/xor.c	operations/zjmp.c	\
		operations/ldi.c	operations/sti.c	operations/fork.c	\
		operations/lld.c	operations/lldi.c	operations/lfork.c	\
		operations/aff.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))
_INCS = vm.h
INCS = $(addprefix $(INC_DIR)/,$(_INCS))

OBJ_FLAGS += -I$(INC_DIR)
OBJ_FLAGS += -I../common
OBJ_FLAGS += $(foreach lib,$(LIBS),-I$(LIB_DIR)/$(lib)/includes)

ifeq ($(STRICT),true)
	OBJ_FLAGS += -Wall -Wextra -Werror
endif
ifeq ($(DEBUG),true)
	OBJ_FLAGS += -g
endif

FLAGS += $(foreach lib,$(LIBS),-L$(LIB_DIR)/$(lib) -l$(lib:lib%=%))
FLAGS += -framework OpenGL -framework AppKit

############################		  Rules 		############################

all: $(LIBS) $(NAME)

$(LIBS):
	@$(MAKE) -C $(LIB_DIR)/$@

$(OBJ_DIR):
	@mkdir -p $@
	@mkdir -p $@/operations
	@mkdir -p $@/draw

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@gcc $(OBJ_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@gcc $(FLAGS) -o $@ $^
	@echo "$(OK_COLOR)Build vm complete$(NO_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(DANGER_COLOR)Object files cleared$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DANGER_COLOR)Build cleared$(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean

#	by rschuppe