/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:29 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 22:45:43 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_add(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	int	i;
	int	arg[3];

	(void)labels;
	i = 0;
	while (i < 3)
	{
		arg[i] = ft_atoi(args->lexem->value);
		if (i != 2)
			args = args->next->next;
		i++;
	}
	i = 0;
	ft_write_program(program, bytes, 1, 0x04);
	ft_write_program(program, bytes, 1, 0b01010100);
	while (i < 3)
	{
		ft_write_program(program, bytes, 1, arg[i]);
		i++;
	}
}

void	ft_sub(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	int	i;
	int	arg[3];

	(void)labels;
	i = 0;
	while (i < 3)
	{
		arg[i] = ft_atoi(args->lexem->value);
		if (i != 2)
			args = args->next->next;
		i++;
	}
	i = 0;
	ft_write_program(program, bytes, 1, 0x05);
	ft_write_program(program, bytes, 1, 0b01010100);
	while (i < 3)
	{
		ft_write_program(program, bytes, 1, arg[i]);
		i++;
	}
}

void	ft_st(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	t_lexem	*arg[2];
	int		start;

	start = *bytes;
	arg[0] = args->lexem;
	arg[1] = args->next->next->lexem;
	ft_write_program(program, bytes, 1, 0x03);
	if (arg[1]->type == REG)
		ft_write_program(program, bytes, 1, 0b01010000);
	else
		ft_write_program(program, bytes, 1, 0b01110000);
	ft_write_program(program, bytes, 1, ft_atoi(arg[0]->value));
	if (arg[1]->type == INDIR_LABEL)
	{
		ft_add_2_sb(labels, 2, *bytes,
					arg[1]->value)->idxs->start = start;
		ft_write_program(program, bytes, 2, 0xcccc);
	}
	else if (arg[1]->type == INDIR)
		ft_write_program(program, bytes, 2, ft_atoi(arg[1]->value));
	else
		ft_write_program(program, bytes, 1, ft_atoi(arg[1]->value));
}
