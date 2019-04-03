/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:43:11 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 14:51:19 by rtroll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_arg_code(t_lexem **arg)
{
	int result;
	int i;
	int j;

	result = 0;
	i = 0;
	j = 3;
	while (i < 3)
	{
		if (arg[i]->type == DIR_LABEL || arg[i]->type == DIR)
			result |= DIR_CODE << (j * 2);
		if (arg[i]->type == INDIR_LABEL || arg[i]->type == INDIR)
			result |= IND_CODE << (j * 2);
		if (arg[i]->type == REG)
			result |= REG_CODE << (j * 2);
		i++;
		j--;
	}
	return (result);
}

static void	ft_args(t_lexem **arg, t_lex_list *args)
{
	int i;

	i = 0;
	while (i < 3)
	{
		arg[i] = args->lexem;
		if (i != 2)
			args = args->next->next;
		i++;
	}
}

static void	ft_write_normal(char **program, unsigned int *bytes,
		t_lexem **arg, int i)
{
	if (arg[i]->type == DIR)
		ft_write_program(program, bytes, 4, ft_atoi(arg[i]->value));
	if (arg[i]->type == INDIR)
		ft_write_program(program, bytes, 2, ft_atoi(arg[i]->value));
	if (arg[i]->type == REG)
		ft_write_program(program, bytes, 1, ft_atoi(arg[i]->value));
}

void		ft_and(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	t_lexem	*arg[3];
	int		i;
	int		start;

	start = *bytes;
	ft_args(arg, args);
	ft_write_program(program, bytes, 1, 0x06);
	ft_write_program(program, bytes, 1, ft_arg_code(arg));
	i = -1;
	while (++i < 3)
	{
		if (arg[i]->type == DIR_LABEL)
		{
			ft_add_2_sb(labels, 4, *bytes, arg[i]->value)->idxs->start = start;
			ft_write_program(program, bytes, 4, 0xcccccccc);
		}
		else if (arg[i]->type == INDIR_LABEL)
		{
			ft_add_2_sb(labels, 2, *bytes, arg[i]->value)->idxs->start = start;
			ft_write_program(program, bytes, 2, 0xcccc);
		}
		else
			ft_write_normal(program, bytes, arg, i);
	}
}

void		ft_or(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	t_lexem	*arg[3];
	int		i;
	int		start;

	start = *bytes;
	ft_args(arg, args);
	ft_write_program(program, bytes, 1, 0x07);
	ft_write_program(program, bytes, 1, ft_arg_code(arg));
	i = -1;
	while (++i < 3)
	{
		if (arg[i]->type == DIR_LABEL)
		{
			ft_add_2_sb(labels, 4, *bytes, arg[i]->value)->idxs->start = start;
			ft_write_program(program, bytes, 4, 0xcccccccc);
		}
		else if (arg[i]->type == INDIR_LABEL)
		{
			ft_add_2_sb(labels, 2, *bytes, arg[i]->value)->idxs->start = start;
			ft_write_program(program, bytes, 2, 0xcccc);
		}
		else
			ft_write_normal(program, bytes, arg, i);
	}
}
