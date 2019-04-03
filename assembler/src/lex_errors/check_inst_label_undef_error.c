/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_label_undef_error.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:43:43 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 22:43:49 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_error_instruction(char *value)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (ft_strcmp(g_op_tab[i].cmd, value) == 0)
			return (0);
		i++;
	}
	return (NON_EXISTENT_VALUE);
}

int		check_error_dir_label(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return (0);
}

int		check_error_indir_label(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return (0);
}

int		check_error_undef(char *value)
{
	(void)value;
	return (NON_EXISTENT_LEXEM);
}
