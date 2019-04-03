/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:05 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 10:25:00 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_lfork(t_env *env, t_carriage *carriage, t_arg *args)
{
	int		new_pos;

	new_pos = calc_mem_addr(carriage->position, args[0].content, false);
	create_carriage(env, carriage, new_pos);
	VERB_LEVEL(SHOW_OPS) && ft_printf("P%5d | lfork %d (%d)\n",
		carriage->id, args[0].content, carriage->position + args[0].content);
	return (-1);
}
