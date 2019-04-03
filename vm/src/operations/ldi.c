/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:26:57 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:58:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ldi(t_env *env, t_carriage *carriage, t_arg *args)
{
	int	value[2];
	int offset;

	value[0] = args[0].content;
	if (DIFF_ENDIAN && (args[0].type == REG_CODE || args[0].type == IND_CODE))
		swap_bytes(&value[0], sizeof(int));
	value[1] = args[1].content;
	if (DIFF_ENDIAN && args[1].type == REG_CODE)
		swap_bytes(&value[1], sizeof(int));
	offset = value[0] + value[1];
	set_reg_value(carriage, args[2].value,
		get_mem_value(env, carriage, offset, true), false);
	if (VERB_LEVEL(SHOW_OPS))
	{
		ft_printf("P%5d | ldi %d %d r%d\n",
			carriage->id, value[0], value[1], args[2].value);
		ft_printf("%8| -> load from %d + %d = %d (with pc and mod %d)\n",
			value[0], value[1], offset, carriage->position + offset % IDX_MOD);
	}
	return (-1);
}
