/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:23:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 16:08:06 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	calc_mem_addr(int start, int offset, bool truncat)
{
	int	mempos;

	truncat && (offset %= IDX_MOD);
	mempos = (start + offset) % MEM_SIZE;
	(mempos < 0) && (mempos = MEM_SIZE + mempos);
	return (mempos);
}

int	get_mem_value_ex(t_env *env, int mempos, int bytes, bool convert_endian)
{
	int	i;
	int	result;

	i = -1;
	result = 0;
	if (convert_endian)
		while (++i < bytes)
			result |=
				*(env->field + (mempos + bytes - 1 - i) % MEM_SIZE) << (8 * i);
	else
		while (++i < bytes)
			result |=
				*(env->field + (mempos + i) % MEM_SIZE) << (8 * i);
	if (result >> ((4 - bytes) * 8 - 1) & 1)
	{
		i = -1;
		while (++i < (4 - bytes))
			result |= 0xFF << (8 * (bytes + i));
	}
	return (result);
}

int	get_mem_value(t_env *env, t_carriage *carriage, int offset, bool truncat)
{
	unsigned char	value[4];
	int				mempos;

	mempos = calc_mem_addr(carriage->position, offset, truncat);
	value[0] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[1] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[2] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[3] = *(env->field + mempos % MEM_SIZE);
	return (*((int*)value));
}

int	set_mem_value(t_env *env, t_carriage *carriage, int offset, int value)
{
	int mempos;

	mempos = calc_mem_addr(carriage->position, offset, true);
	env->field[mempos] = (unsigned char)((value) & 0xFF);
	if (env->visualise)
		draw_set_mem_cell_color(env, mempos, carriage->color);
	mempos = (mempos + 1) % MEM_SIZE;
	env->field[mempos] = (unsigned char)((value >> 8) & 0xFF);
	if (env->visualise)
		draw_set_mem_cell_color(env, mempos, carriage->color);
	mempos = (mempos + 1) % MEM_SIZE;
	env->field[mempos] = (unsigned char)((value >> 16) & 0xFF);
	if (env->visualise)
		draw_set_mem_cell_color(env, mempos, carriage->color);
	mempos = (mempos + 1) % MEM_SIZE;
	env->field[mempos] = (unsigned char)(value >> 24);
	if (env->visualise)
		draw_set_mem_cell_color(env, mempos, carriage->color);
	mempos = (mempos + 1) % MEM_SIZE;
	return (mempos - 4);
}
