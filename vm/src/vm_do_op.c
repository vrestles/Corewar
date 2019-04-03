/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 16:16:40 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op_func	g_op_funcs[] = {
	NULL,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

inline static int	get_cmd_length_helper(
	t_env *env, t_carriage *carriage, int codage_octal, int *len)
{
	uint8_t	args_types;

	if (codage_octal)
	{
		args_types = get_mem_value_ex(env,
			calc_mem_addr(carriage->position, 1, false), 1, false);
		(*len)++;
	}
	else
		args_types = T_DIR << 6;
	return (args_types);
}

static int			get_cmd_length(t_env *env, t_carriage *carriage, t_op *op)
{
	int		len;
	int		i;
	uint8_t	args_types;
	uint8_t	arg_type;

	len = 1;
	if (op)
	{
		args_types = get_cmd_length_helper(
			env, carriage, op->codage_octal, &len);
		i = op->arg_count;
		while (i)
		{
			arg_type = ARG_TYPE(args_types, i - 1);
			arg_type == DIR_CODE && op->dir_ind_size && (arg_type = IND_CODE);
			if (arg_type == REG_CODE)
				len++;
			else if (arg_type == IND_CODE)
				len += 2;
			else if (arg_type == DIR_CODE)
				len += 4;
			i--;
		}
	}
	return (len);
}

int					vm_do_op(t_env *env, t_carriage *carriage)
{
	t_op	*op;
	t_arg	*args;
	int		zjmp;
	int		len;

	len = 1;
	zjmp = -1;
	if ((op = get_op(carriage->op_code)))
	{
		len = get_cmd_length(env, carriage, op);
		if (vm_get_args(env, carriage, &args))
			zjmp = g_op_funcs[carriage->op_code](env, carriage, args);
		if (args)
			free(args);
		if (VERB_LEVEL(SHOW_PC_MOVES) && zjmp == -1)
			print_move(env, carriage->position, len);
	}
	zjmp = zjmp != -1 ? zjmp : calc_mem_addr(carriage->position, len, true);
	if (env->visualise)
		draw_move_carriage(env, carriage->position, zjmp, 0xFFFFFF);
	carriage->position = zjmp;
	return (1);
}
