/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:35:19 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:26:10 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_lld(t_env *env, t_carriage *carriage, t_arg *args)
{
	int value;

	value = (args[0].type == DIR_CODE) ? args[0].value : args[0].content;
	if (set_reg_value(carriage, args[1].value, value, false))
		carriage->carry = !value;
	if (VERB_LEVEL(SHOW_OPS))
	{
		swap_bytes(&value, sizeof(value));
		ft_printf("P%5d | lld %d r%d\n", carriage->id, value, args[1].value);
	}
	return (-1);
}
