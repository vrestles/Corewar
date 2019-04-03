/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:32:44 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:58:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_xor(t_env *env, t_carriage *carriage, t_arg *args)
{
	int value[2];
	int	result;

	value[0] = (args[0].type == DIR_CODE) ? args[0].value : args[0].content;
	value[1] = (args[1].type == DIR_CODE) ? args[1].value : args[1].content;
	result = value[0] ^ value[1];
	if (set_reg_value(carriage, args[2].value, result, false))
		carriage->carry = !result;
	if (VERB_LEVEL(SHOW_OPS))
	{
		if (DIFF_ENDIAN)
		{
			swap_bytes(&value[0], sizeof(value[0]));
			swap_bytes(&value[1], sizeof(value[1]));
		}
		ft_printf("P%5d | xor %d %d r%d\n",
			carriage->id, value[0], value[1], args[2].value);
	}
	return (-1);
}
