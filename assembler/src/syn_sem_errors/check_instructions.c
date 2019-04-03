/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:25:51 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 22:44:38 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_bytmap_offset(t_lex_list *lexem_lst)
{
	if (lexem_lst->lexem->type == REG)
		return (0);
	else if (lexem_lst->lexem->type == DIR
			|| lexem_lst->lexem->type == DIR_LABEL)
		return (1);
	else if (lexem_lst->lexem->type == INDIR
			|| lexem_lst->lexem->type == INDIR_LABEL)
		return (2);
	return (-1);
}

static int	check_instruct_args(
		t_lex_list *lexem_lst, t_errors **error, t_arg_type arg_type)
{
	int offset;

	if ((offset = get_bytmap_offset(lexem_lst)) == -1)
	{
		push_back_errors_list(error, SEMANTIC,
				INVALID_TYPE_OF_ARGUMENT, lexem_lst->lexem);
		return (0);
	}
	if (!(arg_type & (1 << offset)))
	{
		push_back_errors_list(error, SEMANTIC,
				INVALID_TYPE_OF_ARGUMENT, lexem_lst->lexem);
		return (0);
	}
	return (1);
}

static void	find_instruct_errors_helper(
		t_lex_list *lexem_lst, t_errors **error, t_lex_list *head)
{
	if (lexem_lst)
	{
		if (lexem_lst->lexem->type == SEP && !lexem_lst->next)
			push_back_errors_list(error, SYNTACTIC,
					EXCESS_SEPARATOR, lexem_lst->lexem);
		else
			push_back_errors_list(error, SEMANTIC,
					INVALID_NUMBER_OF_ARGUMENT, head->lexem);
	}
}

void		check_instructions(t_lex_list *lexem_lst, t_errors **error)
{
	int			i;
	t_op		*op;
	t_lex_list	*head;

	head = lexem_lst;
	op = get_op_by_name(lexem_lst->lexem->value);
	i = -1;
	while (++i < op->arg_count)
	{
		lexem_lst = lexem_lst->next;
		if (!lexem_lst)
		{
			return (push_back_errors_list(error, SEMANTIC,
					INVALID_NUMBER_OF_ARGUMENT, head->lexem));
		}
		if (!check_instruct_args(lexem_lst, error, op->arg_type[i]))
			return ;
		lexem_lst = lexem_lst->next;
		if (i + 1 == op->arg_count)
			break ;
		else if (!lexem_lst || lexem_lst->lexem->type != SEP)
			return (push_back_errors_list(error, SYNTACTIC,
					MISSING_SEPARATOR, head->lexem));
	}
	find_instruct_errors_helper(lexem_lst, error, head);
}
