/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/28 14:50:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, t_arg *args)
{
	if (VERB_LEVEL(SHOW_OPS))
		ft_printf("P%5d | zjmp %d %s\n",
			carriage->id, args[0].content, carriage->carry ? "OK" : "FAILED");
	return (carriage->carry ?
		calc_mem_addr(carriage->position, args[0].content, true) : -1);
}
