/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:07:47 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 11:37:04 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			get_arg_value(t_env *env, int mempos, t_op *op, t_arg *arg)
{
	int type_size;

	type_size = 0;
	if (arg->type == REG_CODE)
	{
		type_size = sizeof(char);
		arg->value = get_mem_value_ex(env, mempos, type_size, false);
	}
	else if (arg->type == IND_CODE)
	{
		type_size = sizeof(short);
		arg->value = get_mem_value_ex(env, mempos, type_size, true);
	}
	else if (arg->type == DIR_CODE)
	{
		type_size = op->dir_ind_size ? sizeof(short) : sizeof(int);
		arg->value = get_mem_value_ex(env, mempos, type_size, false);
	}
	return (type_size);
}

static int			get_arg_content(
	t_env *env, t_carriage *carriage, t_op *op, t_arg *arg)
{
	short	short_arg;

	if (arg->type == REG_CODE)
		return (get_reg_value(carriage, arg->value, &arg->content, false));
	else if (arg->type == IND_CODE)
		arg->content = get_mem_value(
			env, carriage, arg->value, op->op_code != 13);
	else if (arg->type == DIR_CODE)
	{
		if (op->dir_ind_size)
		{
			short_arg = arg->value;
			if (DIFF_ENDIAN)
				swap_bytes(&short_arg, sizeof(short));
			arg->content = short_arg;
		}
		else
		{
			arg->content = arg->value;
			if (DIFF_ENDIAN)
				swap_bytes(&arg->content, sizeof(int));
		}
	}
	return (true);
}

inline static bool	is_arg_types_valid(t_op *op, uint8_t args_types)
{
	return (op->arg_type[0] & (1 << (ARG_TYPE(args_types, 0) - 1))
		&& (op->arg_count < 2
			|| op->arg_type[1] & (1 << (ARG_TYPE(args_types, 1) - 1)))
		&& (op->arg_count < 3
			|| op->arg_type[2] & (1 << (ARG_TYPE(args_types, 2) - 1))));
}

inline static int	get_args_helper(t_env *env, t_carriage *carriage, t_op *op)
{
	uint8_t	args_types;

	if (op->codage_octal)
	{
		args_types = get_mem_value_ex(env,
			calc_mem_addr(carriage->position, 1, false), 1, false);
		if (!is_arg_types_valid(op, args_types))
			return (false);
	}
	else
		args_types = DIR_CODE << 6;
	return (args_types);
}

bool				vm_get_args(t_env *env, t_carriage *carriage, t_arg **args)
{
	t_op		*op;
	uint8_t		args_types;
	int8_t		i;
	int			move;

	*args = NULL;
	if ((op = get_op(carriage->op_code)))
	{
		if (!(args_types = get_args_helper(env, carriage, op)))
			return (false);
		SECURE_MALLOC(*args = ft_memalloc(op->arg_count * sizeof(t_arg)));
		i = 0;
		move = 1 + op->codage_octal;
		while (i < op->arg_count)
		{
			(*args)[i].type = ARG_TYPE(args_types, i);
			move += get_arg_value(env,
				calc_mem_addr(carriage->position, move, false), op, *args + i);
			if (!get_arg_content(env, carriage, op, (*args) + i))
				return (false);
			i++;
		}
	}
	return (op);
}
