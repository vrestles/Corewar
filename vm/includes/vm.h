/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:48:56 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 17:11:48 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
**	Libs
*/

# include "libft.h"
# include "ft_printf.h"
# include "draw.h"

/*
**	Main header by subject
*/

# include "op.h"

/*
**	Macroses
*/

# define WIN_MARGIN			10
# define CELL_SIZE			4
# define CELL_MARGIN		1
# define WIN_HEIGHT			(CELL_SIZE + CELL_MARGIN * 2) * 64 + WIN_MARGIN * 2
# define WIN_WIDTH			WIN_HEIGHT + 200

# define CHAMP1_COLOR		0x00FF00
# define CHAMP2_COLOR		0x0000FF
# define CHAMP3_COLOR		0xFF0000
# define CHAMP4_COLOR		0xFFFF00

# define COLOR_USAGE		"\x1b[32m"
# define COLOR_ERROR		"\x1b[31m"
# define COLOR_NONE			"\x1b[39m"

# define SHOW_LIVES			1
# define SHOW_CYCLES		2
# define SHOW_OPS			4
# define SHOW_DEATHS		8
# define SHOW_PC_MOVES		16

# define VERB_LEVEL(level)	(env->verb_levels & level)

# define DIFF_ENDIAN		(LITTLE_ENDIAN == BYTE_ORDER)

# define ARG_TYPE(val, num)	((val) >> (8 - (2 * (num + 1))) & 0x3)

# define SECURE_MALLOC(a)	!(a) && throw_error(MEMORY_ERR)

# define STR_ERROR_SYS		COLOR_ERROR"[System Error]: "COLOR_NONE
# define STR_ERROR_READ		COLOR_ERROR"[Read Error]: "COLOR_NONE
# define STR_ERROR_VALID	COLOR_ERROR"[Validation Error]: "COLOR_NONE
# define MEMORY_ERR			STR_ERROR_SYS, "Not enough memory"

# define CYCLE_NUM_MESG		"It is now cycle %d\n", env->acount_cycles

typedef struct	s_arg
{
	int			value;
	t_arg_type	type;
	int			content;
}				t_arg;

/*
**	Structure describe carriage
*/

typedef struct	s_carriage
{
	int				id;
	bool			carry;
	unsigned char	op_code;
	int				last_live_cycle;
	int				cycles_to_execute;
	unsigned int	position;
	unsigned int	registers[REG_NUMBER];
	int				color;
}				t_carriage;

/*
**	Structure describe champion
*/

typedef struct	s_champion
{
	int				nbr_player;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	*exec_code;
	unsigned int	prog_size;
	unsigned int	last_live_cycle;
}				t_champion;

/*
**	Structure describe vm state
**	last_cycle_*	-	переменная хранящая номер цикла в котором произошло
**						какое-то действие
**	rcount_*		-	(repeat counter) счетчик периодически скидывающий
**						свое значение (0)
**	acount_*		-	(absolute counter) абсолютный счетчик, который считает
**						не скидывает значения до конца выполнения программы
*/

typedef struct	s_env
{
	unsigned char	field[MEM_SIZE];

	bool			visualise;
	bool			show_aff;
	int8_t			verb_levels;
	int				dump_nbr_cycle;

	t_champion		**champions;
	t_list			*carriages;
	int				last_carriage_id;
	int				carriages_count;

	int8_t			last_live_champ;
	int				cycles_to_die;

	int				last_cycle_change_ctd;
	int				last_cycle_check;

	int				rcount_lives;
	int				acount_cycles;
	int				acount_checks;

	t_mlx			*mlx;
	t_img			*mem_line[64];
}				t_env;

typedef	int	(*t_op_func)(t_env *env, t_carriage *carriage, t_arg *args);

int				g_carriage_colors[4];

t_op			*get_op(char op_code);

/*
**	read args and champions
*/

int				read_args(int argc, char **argv, t_env *env);
void			put_champ_on_arr(
	int nbr_player, char *argv, t_env *env, int *mask);
void			check_arr_champions(int count_champion, int *mask);

/*
**	main vm functions
*/

void			vm_init(t_env *env);
void			vm_loop(t_env *env);
int				vm_check_die(t_env *env);
void			vm_destroy(t_env *env);

bool			vm_get_args(t_env *env, t_carriage *carriage, t_arg **args);
int				vm_do_op(t_env *env, t_carriage *carriage);

/*
**	carriage functions
*/

t_carriage		*create_carriage(t_env *env, t_carriage *parent, int pos);
t_list			*remove_carriage(t_env *env, t_list *die_carriage);

/*
**	carriage registers functions
*/

bool			get_reg_value(
	t_carriage *carriage, char idx, int *value, bool convert_endian);
bool			set_reg_value(
	t_carriage *carriage, char idx, int value, bool convert_endian);

/*
**	vm memory functions
*/

int				calc_mem_addr(int start, int offset, bool truncat);
int				get_mem_value(
	t_env *env, t_carriage *carriage, int offset, bool truncat);
int				get_mem_value_ex(
	t_env *env, int mempos, int bytes, bool convert_endian);
int				set_mem_value(
	t_env *env, t_carriage *carriage, int offset, int value);

/*
**	vm operations
*/

int				op_live(t_env *env, t_carriage *carriage, t_arg *args);
int				op_ld(t_env *env, t_carriage *carriage, t_arg *args);
int				op_st(t_env *env, t_carriage *carriage, t_arg *args);
int				op_add(t_env *env, t_carriage *carriage, t_arg *args);
int				op_sub(t_env *env, t_carriage *carriage, t_arg *args);
int				op_and(t_env *env, t_carriage *carriage, t_arg *args);
int				op_or(t_env *env, t_carriage *carriage, t_arg *args);
int				op_xor(t_env *env, t_carriage *carriage, t_arg *args);
int				op_zjmp(t_env *env, t_carriage *carriage, t_arg *args);
int				op_ldi(t_env *env, t_carriage *carriage, t_arg *args);
int				op_sti(t_env *env, t_carriage *carriage, t_arg *args);
int				op_fork(t_env *env, t_carriage *carriage, t_arg *args);
int				op_lld(t_env *env, t_carriage *carriage, t_arg *args);
int				op_lldi(t_env *env, t_carriage *carriage, t_arg *args);
int				op_lfork(t_env *env, t_carriage *carriage, t_arg *args);
int				op_aff(t_env *env, t_carriage *carriage, t_arg *args);

/*
**	utils functions
*/

void			swap_bytes(void *memory, int size);
int				cw_atoi(const char *str, const char *error);

/*
**	Print
*/

int				print_move(t_env *env, int curpos, int len);
void			print_players(t_env *env);
void			print_memory(const void *memory, int size);

/*
**	Visualise
*/

void			draw_init(t_env *env);
int				draw_loop(t_env *env);
void			draw_carriage(t_env *env, int cell, int color);
void			draw_move_carriage(
	t_env *env, int old_cell, int new_cell, int color);
void			draw_set_mem_cell_color(t_env *env, int cell, int color);
void			draw_info(t_env *env, int *offset);
void			draw_players(t_env *env, int *offset);

#endif
