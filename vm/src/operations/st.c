/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:15:01 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:26:20 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_st(t_env *env, t_carriage *carriage, t_arg *args)
{
	if (args[1].type == REG_CODE)
		set_reg_value(carriage, args[1].value, args[0].content, false);
	else
		set_mem_value(env, carriage, args[1].value, args[0].content);
	if (VERB_LEVEL(SHOW_OPS))
		ft_printf("P%5d | st r%d %d\n",
			carriage->id, args[0].value, args[1].value);
	return (-1);
}
