############################		Variables		############################
include ../var.mk

NAME = ../$(ASM_NAME)

LIB_DIR = ../libs
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes

LIBS = libft libftprintf

SRCS =	main.c												\
		op.c												\
		print_errors.c										\
		get_lexems/get_comm_str_lexems.c					\
		get_lexems/get_dir_indir_reg.c						\
		get_lexems/get_instruct_label.c						\
		get_lexems/get_sep_undef.c							\
		get_lexems/get_lex_help_functions.c					\
		lex_errors/check_comm_str_error.c					\
		lex_errors/check_inst_label_undef_error.c			\
		lex_errors/check_lex_errors.c						\
		lex_errors/check_lex_type.c							\
		lex_errors/check_num_reg_error.c					\
		syn_sem_errors/check_code.c							\
		syn_sem_errors/check_instructions.c					\
		syn_sem_errors/list_labels_stuff.c					\
		syn_sem_errors/check_com_help_functions.c			\
		syn_sem_errors/check_labels.c						\
		syn_sem_errors/check_commands.c						\
		syn_sem_errors/check_syntactic_semantic_errors.c	\
		utils/delete_1.c									\
		utils/delete_2.c									\
		utils/file_stuff.c									\
		utils/list_stuff.c									\
		utils/tokens_stuff.c								\
		bytecode/and.c										\
		bytecode/hash.c										\
		bytecode/instructions.c								\
		bytecode/label.c									\
		bytecode/ldi_lldi.c									\
		bytecode/lld.c										\
		bytecode/name_comment.c								\
		bytecode/sti.c										\
		bytecode/xor.c										\
		bytecode/compiler.c									\
		bytecode/instructions_2.c							\
		bytecode/ld.c										\
		bytecode/print_bytes.c								\
		bytecode/to_code.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))
_INCS = asm.h
INCS = $(addprefix $(INC_DIR)/,$(_INCS))

FLAGS += -I$(INC_DIR)
OBJ_FLAGS += -I../common
FLAGS += $(foreach lib,$(LIBS),-I$(LIBS_DIR)/$(lib)/includes)

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

############################		  Rules 		############################

all: $(LIBS) $(NAME)

$(LIBS):
	@$(MAKE) -C $(LIB_DIR)/$@

$(OBJ_DIR):
	@mkdir -p $@
	@mkdir -p $@/utils
	@mkdir -p $@/get_lexems
	@mkdir -p $@/lex_errors
	@mkdir -p $@/syn_sem_errors
	@mkdir -p $@/bytecode

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@gcc $(OBJ_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@gcc $(FLAGS) -o $@ $^
	@echo "$(OK_COLOR)Build assembler complete$(NO_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(DANGER_COLOR)Object files cleared$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DANGER_COLOR)Build cleared$(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean
