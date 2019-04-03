/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 11:59:24 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 16:09:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			g_carriage_colors[4] = {
	CHAMP1_COLOR, CHAMP2_COLOR, CHAMP3_COLOR, CHAMP4_COLOR
};

static int	mlx_close(void)
{
	exit(0);
	return (1);
}

static void	draw_render(t_env *env)
{
	int		i;
	int		pos_offset;

	i = 0;
	mlx_clear_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	while (i < 64)
	{
		mlx_put_image_to_window(
			env->mlx->mlx_ptr,
			env->mlx->win_ptr,
			env->mem_line[i]->img_ptr,
			WIN_MARGIN, WIN_MARGIN + i * (CELL_SIZE + CELL_MARGIN * 2));
		i++;
	}
	pos_offset = 0;
	draw_info(env, &pos_offset);
	draw_players(env, &pos_offset);
}

static void	draw_init_mem_field(t_env *env)
{
	int i;

	i = 0;
	while (i < 64)
	{
		env->mem_line[i] = ft_create_image(env->mlx,
			64 * (CELL_SIZE + CELL_MARGIN * 2),
			CELL_SIZE + CELL_MARGIN * 2);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		draw_set_mem_cell_color(env, i, 0x9E9E9E);
		i++;
	}
}

void		draw_init(t_env *env)
{
	if (env->visualise)
	{
		env->mlx = ft_create_window(WIN_WIDTH, WIN_HEIGHT, "Corewar - VM");
		mlx_hook(env->mlx->win_ptr, 17, 1L << 17, mlx_close, NULL);
		mlx_loop_hook(env->mlx->mlx_ptr, draw_loop, env);
		draw_init_mem_field(env);
	}
}

int			draw_loop(t_env *env)
{
	if (vm_check_die(env))
	{
		vm_loop(env);
		draw_render(env);
	}
	else
	{
		vm_destroy(env);
		exit(1);
	}
	return (1);
}
