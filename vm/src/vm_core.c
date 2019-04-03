/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:50:41 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 16:08:57 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_carriage(t_env *env, int champ_idx, int position)
{
	int			i;
	t_carriage	*carriage;

	carriage = create_carriage(env, NULL, position);
	carriage->color = g_carriage_colors[champ_idx];
	carriage->registers[0] = -(champ_idx + 1);
	if (DIFF_ENDIAN)
		swap_bytes(&carriage->registers[0], sizeof(carriage->registers[0]));
	ft_memcpy(env->field + carriage->position,
		env->champions[champ_idx]->exec_code,
		env->champions[champ_idx]->prog_size);
	if (env->visualise)
	{
		draw_carriage(env, position, 0xFFFFFF);
		i = 0;
		while (i < (int)env->champions[champ_idx]->prog_size)
		{
			draw_set_mem_cell_color(env,
				carriage->position + i, carriage->color);
			i++;
		}
	}
}

void		vm_init(t_env *env)
{
	int8_t		i;
	int			offset;
	int8_t		champions_count;

	if (env->visualise)
		draw_init(env);
	i = 0;
	while (env->champions[i])
		i++;
	champions_count = i;
	offset = MEM_SIZE / champions_count;
	i = 0;
	while (env->champions[i])
	{
		init_carriage(env, i, offset * i);
		env->last_live_champ = i;
		i++;
	}
	env->cycles_to_die = CYCLE_TO_DIE;
	print_players(env);
}

void		vm_destroy(t_env *env)
{
	int i;

	i = 0;
	while (env->champions[i])
	{
		free(env->champions[i]->exec_code);
		free(env->champions[i]);
		i++;
	}
	free(env->champions);
	free(env);
}
