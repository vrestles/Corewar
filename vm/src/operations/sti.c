/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:17:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:58:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sti(t_env *env, t_carriage *carriage, t_arg *args)
{
	int	value[2];
	int	offset;

	value[0] = args[1].content;
	if (DIFF_ENDIAN && (args[1].type == REG_CODE || args[1].type == IND_CODE))
		swap_bytes(&value[0], sizeof(int));
	value[1] = args[2].content;
	if (DIFF_ENDIAN && args[2].type == REG_CODE)
		swap_bytes(&value[1], sizeof(int));
	offset = value[0] + value[1];
	set_mem_value(env, carriage, offset, args[0].content);
	if (VERB_LEVEL(SHOW_OPS))
	{
		ft_printf("P%5d | sti r%d %d %d\n",
			carriage->id, args[0].value, value[0], value[1]);
		ft_printf("%8 | -> store to %d + %d = %d (with pc and mod %d)\n",
			value[0], value[1], offset, carriage->position + offset % IDX_MOD);
	}
	return (-1);
}
