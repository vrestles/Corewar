/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:12 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 21:13:11 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ASM_H
# define ASM_ASM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "op.h"

# define CHECK_NULL(x)	if (x == NULL) return (NULL)

# define FIRST_BYTE		0x000000ff

# define COLOR_BOLD		"\x1b[1m"
# define COLOR_ERROR	"\x1b[1;31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_NONE		"\x1b[0m"

enum	e_prog_errors
{
	NO_FILE = 1,
	MORE_THAN_ONE_FILE = 2,
	CANT_OPEN_FILE = 3,
	EMPTY_FILE = 4,
	ERRORS_IN_CODE = 5
};

enum	e_tokens
{
	COMMAND = 1,
	STRING = 2,
	INSTRUCT = 3,
	COMMENT = 4,
	LABEL = 5,
	REG = 6,
	SEP = 7,
	DIR = 8,
	DIR_LABEL = 9,
	INDIR = 10,
	INDIR_LABEL = 11,
	UNDEF = 12
};

enum	e_errors
{
	LEXICAL = 1,
	SYNTACTIC = 2,
	SEMANTIC = 3
};

enum	e_lexical_errors
{
	EMPTY_VALUE = 1,
	NON_EXISTENT_VALUE = 2,
	OUT_OF_RANGE_VALUE = 3,
	NON_VALID_VALUE = 4,
	NON_EXISTENT_LEXEM = 5
};

enum	e_syntactic_errors
{
	WRONG_PROGRAM_STRUCTURE = 1,
	MISSING_SEPARATOR,
	EXCESS_SEPARATOR,
	EXCESS_INSTUCTION_IN_LINE
};

enum	e_semantic_errors
{
	NO_ARGUMENTS = 1,
	NO_CODE,
	NO_COMMANDS,
	INVALID_NUMBER_OF_ARGUMENT,
	INVALID_TYPE_OF_ARGUMENT,
	INVALID_LEXEM_SEQUENCE,
	UNDECLARED_IDENTIFIER,
	EXCESS_SIZE_COMMAND,
	COMMAND_NAME_NOT_FOUND,
	COMMAND_COMMENT_NOT_FOUND,
	COMMAND_REDEFINITION,
	CONSTANT_REDEFINITION
};

typedef struct			s_lines
{
	int					count;
	char				**line;
}						t_lines;

typedef struct			s_lexem
{
	int					type;
	int					line;
	int					start;
	char				*value;
}						t_lexem;

typedef struct			s_lex_list
{
	struct s_lexem		*lexem;
	struct s_lex_list	*next;
}						t_lex_list;

typedef struct			s_tokens
{
	int					count;
	struct s_lex_list	**tokenlst;

}						t_tokens;

typedef struct			s_cursor
{
	int					line;
	int					pos;
}						t_cursor;

typedef struct			s_errors
{
	int					error_code[2];
	t_lexem				*lexem;
	struct s_errors		*next;
}						t_errors;

typedef struct			s_lab_list
{
	t_lexem				*lexem;
	struct s_lab_list	*next;
}						t_lab_list;

typedef struct			s_asm_list
{
	unsigned int		index;
	int					start;
	unsigned int		size;
	struct s_asm_list	*next;
}						t_asm_list;

typedef struct			s_list_label
{
	struct s_list_label	*next;
	struct s_label		*label;
}						t_list_label;

typedef struct			s_label
{
	char				*name;
	int					start_byte;
	t_asm_list			*idxs;
}						t_label;

typedef char			t_bool;

t_op					*get_op_by_name(char *cmd);

t_bool					is_file_name_valid(char *str);

t_lines					*read_file_into_lines(int fd, char **line);
t_tokens				*get_tokens(t_lines *lines);
void					get_lex_errors(t_tokens *tokens, t_errors **res);
void					get_syn_sem_errors(t_tokens *tokens, t_errors **err);

void					push_back_lex_list(t_lex_list **alst, t_lexem *content);
void					push_back_errors_list(t_errors **alst, int err,
		int addit_err, t_lexem *lexem);

t_bool					is_label_char(char c);
t_bool					is_undefined(char c);
t_bool					is_digit_sign(char c);
int						ft_isalpha_small(int c);

t_lexem					*get_command(char *str, t_cursor *cur);
t_lexem					*get_string(t_lines *lines, t_cursor *cur);
t_lexem					*get_comment(char *str, t_cursor *cur);
t_lexem					*get_separator(char *str, t_cursor *cur);
t_lexem					*get_direct(char *str, t_cursor *cur);
t_lexem					*get_direct_label(char *str, t_cursor *cur);
t_lexem					*get_register(char *str, t_cursor *cur);
t_lexem					*get_instruction(char *str, t_cursor *cur, int len);
t_lexem					*get_indir_num(char *str, t_cursor *cur);
t_lexem					*get_undef(char *str, t_cursor *cur);
t_lexem					*get_indir_label(char *str, t_cursor *cur);
t_lexem					*get_label(char *str, t_cursor *cur, int len);

t_lexem					*check_instuct_label_reg(char *str, t_cursor *cur);
t_lexem					*check_indir_or_label(char *str, t_cursor *cur);
t_lexem					*check_label_or_undef(char *str, t_cursor *cur);

int						check_error_string(char *value);
int						check_error_command(char *value);
int						check_error_reg(char *value);
int						check_error_dir(char *value);
int						check_error_indir(char *value);
int						check_error_instruction(char *value);
int						check_error_dir_label(char *value);
int						check_error_indir_label(char *value);
int						check_error_undef(char *value);

void					check_commands(t_tokens *tokens, t_errors **err);
void					check_code(t_tokens *tokens, t_errors **err);
void					check_instructions(t_lex_list *lst, t_errors **err);

void					print_errors(char *filename, t_errors *lex_errors);

void					delete_str_commas(t_tokens *tokens);
void					delete_lines(t_lines *del);
void					delete_tokens(t_tokens *del);
void					delete_lex_errors(t_errors **del);
void					delete_lexem(t_lexem **del);
void					delete_elem_lex_list(t_lex_list **lst, t_lex_list *del);
void					delete_lex_list(t_lex_list **head);
void					delete_cursor(t_cursor **cur);
void					delete_comments(t_tokens **tokens);

int						count_command_definitions(t_tokens *tokens, char *str);
void					find_fisrt_redef_command(
	t_tokens *tokens, char *str, t_errors **err);
void					push_back_lab_list(t_lab_list **alst, t_lexem *content);
t_lab_list				*generate_lab_list(t_tokens *tokens);
void					find_duplicate_labes(t_lab_list *lab, t_errors **err);
void					find_undeclared_labels(
	t_tokens *tokens, t_lab_list *labels, t_errors **err);
void					delete_lab_list(t_lab_list **lab);

void					ft_to_code(t_tokens *tokens, char *name);
char					*ft_get_extension(char *str, char c);
char					*ft_print_bytes(int number, unsigned int bytes);
int						ft_set_name_comment(t_tokens *tokens, t_header *head);
void					ft_print_error(t_lexem *lexem);
unsigned int			ft_set_program(t_tokens *tokens, char **program,
		int start);
t_label					*ft_find_label(t_list_label *labels, char *name);
void					ft_create_label(t_list_label **labels, char *name,
		int byte);
int						ft_index(char *name);
void					ft_live(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_write_program(char **program, unsigned int *bytes,
		unsigned int size, int code);
void					ft_add_label(t_list_label **labels, char *name,
		unsigned int byte);
t_label					*ft_add_2_sb(t_list_label **labels, int size,
		unsigned int index, char *name);

void					ft_fork(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_lfork(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_aff(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_zjmp(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_ld(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_lld(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_add(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_sub(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_st(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_and(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_or(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_xor(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_lldi(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_ldi(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_sti(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);
void					ft_delete_labels(t_list_label **labels);
void					ft_delete_lab(t_label *label);

#endif
