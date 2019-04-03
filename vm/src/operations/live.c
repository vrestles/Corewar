/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:09 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:26:07 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_live(t_env *env, t_carriage *carriage, t_arg *args)
{
	int		player;
	int		i;

	player = args[0].content;
	VERB_LEVEL(SHOW_OPS) && ft_printf("P%5d | live %d\n", carriage->id, player);
	carriage->last_live_cycle = env->acount_cycles;
	env->rcount_lives++;
	i = 0;
	while (env->champions[i])
	{
		if (i + 1 == -player)
		{
			env->last_live_champ = i;
			env->champions[i]->last_live_cycle = env->acount_cycles;
			VERB_LEVEL(SHOW_LIVES)
				&& ft_printf("Player %d (%s) is said to be alive\n",
					i + 1, env->champions[i]->prog_name);
			break ;
		}
		i++;
	}
	return (-1);
}
