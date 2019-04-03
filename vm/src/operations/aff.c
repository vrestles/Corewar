/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:40 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 13:44:38 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_aff(t_env *env, t_carriage *carriage, t_arg *args)
{
	(void)carriage;
	if (env->show_aff)
	{
		if (DIFF_ENDIAN)
			swap_bytes(&args[0].content, sizeof(args[0].content));
		ft_putstr("Aff: ");
		ft_putchar((char)args[0].content);
		ft_putchar('\n');
	}
	return (-1);
}
