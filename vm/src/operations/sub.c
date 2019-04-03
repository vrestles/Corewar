/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:23:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:58:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sub(t_env *env, t_carriage *carriage, t_arg *args)
{
	int result;

	if (DIFF_ENDIAN)
	{
		swap_bytes(&args[0].content, sizeof(args[0].content));
		swap_bytes(&args[1].content, sizeof(args[0].content));
	}
	result = args[0].content - args[1].content;
	if (set_reg_value(carriage, args[2].value, result, true))
		carriage->carry = !result;
	if (VERB_LEVEL(SHOW_OPS))
		ft_printf("P%5d | sub r%d r%d r%d\n",
			carriage->id, args[0].value, args[1].value, args[2].value);
	return (-1);
}
