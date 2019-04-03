/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:31:50 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 14:51:19 by rtroll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_live(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	int start;

	start = *bytes;
	if (args->lexem->type == DIR && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x01);
		ft_write_program(program, bytes, 4, ft_atoi(args->lexem->value));
	}
	else if (args->lexem->type == DIR_LABEL && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x01);
		ft_add_2_sb(labels, 4, *bytes,
					args->lexem->value)->idxs->start = start;
		ft_write_program(program, bytes, 4, 0xcccccccc);
	}
	else if (args->lexem->type == DIR_LABEL || args->lexem->type == DIR)
		ft_print_error(args->next->lexem);
	else
		ft_print_error(args->lexem);
}

void	ft_fork(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	int start;

	start = *bytes;
	if (args->lexem->type == DIR && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x0c);
		ft_write_program(program, bytes, 2, ft_atoi(args->lexem->value));
	}
	else if (args->lexem->type == DIR_LABEL && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x0c);
		ft_add_2_sb(labels, 2, *bytes,
					args->lexem->value)->idxs->start = start;
		ft_write_program(program, bytes, 2, 0xcccc);
	}
	else if (args->lexem->type == DIR_LABEL || args->lexem->type == DIR)
		ft_print_error(args->next->lexem);
	else
		ft_print_error(args->lexem);
}

void	ft_lfork(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	int start;

	start = *bytes;
	if (args->lexem->type == DIR && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x0f);
		ft_write_program(program, bytes, 2, ft_atoi(args->lexem->value));
	}
	else if (args->lexem->type == DIR_LABEL && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x0f);
		ft_add_2_sb(labels, 2, *bytes,
					args->lexem->value)->idxs->start = start;
		ft_write_program(program, bytes, 2, 0xcccc);
	}
	else if (args->lexem->type == DIR_LABEL || args->lexem->type == DIR)
		ft_print_error(args->next->lexem);
	else
		ft_print_error(args->lexem);
}

void	ft_aff(t_lex_list *args, unsigned int *bytes, t_list_label **labels,
		char **program)
{
	if (args->lexem->type == REG && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x10);
		ft_write_program(program, bytes, 1, 0x00 | 0b01000000);
		ft_write_program(program, bytes, 1, ft_atoi(args->lexem->value));
	}
	else if (args->lexem->type == REG)
		ft_print_error(args->next->lexem);
	else
		ft_print_error(args->lexem);
	(void)labels;
}

void	ft_zjmp(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	int start;

	start = *bytes;
	if (args->lexem->type == DIR && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x09);
		ft_write_program(program, bytes, 2, ft_atoi(args->lexem->value));
	}
	else if (args->lexem->type == DIR_LABEL && (args->next == NULL ||
	args->next->lexem->type == COMMENT))
	{
		ft_write_program(program, bytes, 1, 0x09);
		ft_add_2_sb(labels, 2, *bytes,
					args->lexem->value)->idxs->start = start;
		ft_write_program(program, bytes, 2, 0xcccc);
	}
	else if (args->lexem->type == DIR_LABEL || args->lexem->type == DIR)
		ft_print_error(args->next->lexem);
	else
		ft_print_error(args->lexem);
}
