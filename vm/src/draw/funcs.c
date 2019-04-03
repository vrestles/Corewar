/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:49:14 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 14:50:53 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		draw_carriage(t_env *env, int cell, int color)
{
	int		x;
	int		y;
	int		len;
	t_img	*img;

	img = env->mem_line[cell / 64];
	len = img->size_l / 4;
	cell = cell % 64 * (CELL_SIZE + CELL_MARGIN * 2);
	y = 0;
	while (y < CELL_SIZE + CELL_MARGIN * 2)
	{
		x = 0;
		while (x < CELL_SIZE + CELL_MARGIN * 2)
		{
			if (y < CELL_MARGIN || y >= CELL_SIZE + CELL_MARGIN)
				img->data[(y * len) + (cell + x)] = color;
			else if (x < CELL_MARGIN || x >= CELL_SIZE + CELL_MARGIN)
				img->data[(y * len) + (cell + x)] = color;
			x++;
		}
		y++;
	}
}

inline void	draw_move_carriage(
	t_env *env, int old_cell, int new_cell, int color)
{
	draw_carriage(env, old_cell, 0);
	draw_carriage(env, new_cell, color);
}

void		draw_set_mem_cell_color(t_env *env, int cell, int color)
{
	int		x;
	int		y;
	t_img	*img;
	int		len;

	img = env->mem_line[cell / 64];
	len = img->size_l / 4;
	cell = cell % 64 * (CELL_SIZE + CELL_MARGIN * 2);
	y = CELL_MARGIN;
	while (y < CELL_SIZE + CELL_MARGIN)
	{
		x = CELL_MARGIN;
		while (x < CELL_SIZE + CELL_MARGIN)
		{
			img->data[(y * len) + (cell + x)] = color;
			x++;
		}
		y++;
	}
}

void		draw_info(t_env *env, int *offset)
{
	char *tmp;
	char *str;

	*offset = 0;
	tmp = ft_itoa(env->acount_cycles);
	str = ft_strjoin("Cycles: ", tmp);
	free(tmp);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
		WIN_HEIGHT, WIN_MARGIN + *offset, 0xFFFFFF, str);
	free(str);
	*offset += 25;
	tmp = ft_itoa(env->carriages_count);
	str = ft_strjoin("Processes: ", tmp);
	free(tmp);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
		WIN_HEIGHT, WIN_MARGIN + *offset, 0xFFFFFF, str);
	free(str);
	*offset += 25;
	tmp = ft_itoa(env->cycles_to_die);
	str = ft_strjoin("Cycles to die: ", tmp);
	free(tmp);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
		WIN_HEIGHT, WIN_MARGIN + *offset, 0xFFFFFF, str);
	free(str);
	*offset += 25;
}

void		draw_players(t_env *env, int *offset)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	while (env->champions[i])
	{
		*offset += 25;
		mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
			WIN_HEIGHT, WIN_MARGIN + *offset, g_carriage_colors[i],
			env->champions[i]->prog_name);
		*offset += 25;
		tmp = ft_itoa(env->champions[i]->last_live_cycle);
		str = ft_strjoin("Last live: ", tmp);
		free(tmp);
		mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
			WIN_HEIGHT, WIN_MARGIN + *offset, 0xFFFFFF, str);
		free(str);
		*offset += 25;
		i++;
	}
}
