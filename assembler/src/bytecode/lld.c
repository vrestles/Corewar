/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:40:22 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 14:51:19 by rtroll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_write_size(char **program, unsigned int *bytes,
		unsigned int size, t_lex_list *args)
{
	ft_write_program(program, bytes, 1, 0x02);
	if (size == 4)
		ft_write_program(program, bytes, 1, 0x00 | 0b10010000);
	else
		ft_write_program(program, bytes, 1, 0x00 | 0b11010000);
	ft_write_program(program, bytes, size, ft_atoi(args->lexem->value));
	ft_write_program(program, bytes, 1,
			ft_atoi(args->next->next->lexem->value));
}

static void	ft_write_direct_label(char **program, unsigned int *bytes,
		t_list_label **labels, t_lex_list *args)
{
	int start;

	start = *bytes;
	ft_write_program(program, bytes, 1, 0x02);
	ft_write_program(program, bytes, 1, 0x00 | 0b10010000);
	ft_add_2_sb(labels, 4, *bytes,
				args->lexem->value)->idxs->start = start;
	ft_write_program(program, bytes, 4, 0xcccccccc);
	ft_write_program(program, bytes, 1,
			ft_atoi(args->next->next->lexem->value));
}

static void	ft_write_indirect_label(char **program, unsigned int *bytes,
		t_list_label **labels, t_lex_list *args)
{
	int start;

	start = *bytes;
	ft_write_program(program, bytes, 1, 0x02);
	ft_write_program(program, bytes, 1, 0x00 | 0b11010000);
	ft_add_2_sb(labels, 2, *bytes,
				args->lexem->value)->idxs->start = start;
	ft_write_program(program, bytes, 2, 0xcccc);
	ft_write_program(program, bytes, 1,
			ft_atoi(args->next->next->lexem->value));
}

void		ft_lld(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	if (args->lexem->type == DIR)
		ft_write_size(program, bytes, 4, args);
	else if (args->lexem->type == DIR_LABEL)
		ft_write_direct_label(program, bytes, labels, args);
	else if (args->lexem->type == INDIR)
		ft_write_size(program, bytes, 2, args);
	else if (args->lexem->type == INDIR_LABEL)
		ft_write_indirect_label(program, bytes, labels, args);
}
