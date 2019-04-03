/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexical_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:56:24 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 18:28:42 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_lex_errors(t_lexem *lexem)
{
	if (lexem->type == COMMAND)
		return (check_error_command(lexem->value));
	else if (lexem->type == STRING)
		return (check_error_string(lexem->value));
	else if (lexem->type == INSTRUCT)
		return (check_error_instruction(lexem->value));
	else if (lexem->type == REG)
		return (check_error_reg(lexem->value));
	else if (lexem->type == DIR)
		return (check_error_dir(lexem->value));
	else if (lexem->type == DIR_LABEL)
		return (check_error_dir_label(lexem->value));
	else if (lexem->type == INDIR)
		return (check_error_indir(lexem->value));
	else if (lexem->type == INDIR_LABEL)
		return (check_error_indir_label(lexem->value));
	else if (lexem->type == UNDEF)
		return (check_error_undef(lexem->value));
	return (0);
}

void		get_lex_errors(t_tokens *tokens, t_errors **res)
{
	int			i;
	int			addit_err;
	t_lex_list	*tmp;

	i = 0;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		while (tmp)
		{
			if ((addit_err = check_lex_errors(tmp->lexem)))
				push_back_errors_list(res, LEXICAL, addit_err, tmp->lexem);
			tmp = tmp->next;
		}
		i++;
	}
}
