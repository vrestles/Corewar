/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:49:33 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 19:20:13 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	lexem_in_label_list(t_lexem *lexem, t_lab_list *lab)
{
	if (lab == NULL)
		return (false);
	while (lab)
	{
		if (ft_strcmp(lab->lexem->value, lexem->value) == 0)
			return (true);
		lab = lab->next;
	}
	return (false);
}

static t_bool	address_in_label_list(t_lexem *lexem, t_lab_list *lab)
{
	if (lab == NULL)
		return (false);
	while (lab)
	{
		if (lab->lexem == lexem)
			return (true);
		lab = lab->next;
	}
	return (false);
}

void			find_duplicate_labes(t_lab_list *lab, t_errors **err)
{
	t_lab_list	*tmp;
	t_lab_list	*dup;

	dup = NULL;
	if (lab == NULL)
		return ;
	while (lab)
	{
		tmp = lab;
		while (tmp)
		{
			if (tmp != lab && address_in_label_list(tmp->lexem, dup) == false &&
			ft_strcmp(lab->lexem->value, tmp->lexem->value) == 0)
			{
				push_back_lab_list(&dup, tmp->lexem);
				push_back_errors_list(err, SEMANTIC,
						CONSTANT_REDEFINITION, tmp->lexem);
			}
			tmp = tmp->next;
		}
		lab = lab->next;
	}
	delete_lab_list(&dup);
}

void			find_undeclared_labels(t_tokens *tokens,
									t_lab_list *labels, t_errors **err)
{
	int			i;
	t_lex_list	*tmp;

	i = 0;
	while (i < tokens->count)
	{
		if ((tmp = tokens->tokenlst[i]) != NULL)
		{
			while (tmp)
			{
				if (tmp->lexem->type == DIR_LABEL ||
					tmp->lexem->type == INDIR_LABEL)
					if (lexem_in_label_list(tmp->lexem, labels) == false)
						push_back_errors_list(err, SEMANTIC,
								UNDECLARED_IDENTIFIER, tmp->lexem);
				tmp = tmp->next;
			}
		}
		i++;
	}
}
