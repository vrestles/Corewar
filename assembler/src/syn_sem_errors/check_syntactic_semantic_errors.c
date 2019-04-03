/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:45:43 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 19:14:13 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		find_last_command_line_number(t_tokens *tokens)
{
	int			i;
	int			ret;
	t_lex_list	*tmp;

	i = 0;
	ret = -1;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		if (tmp != NULL)
			if (tmp->lexem->type == COMMAND)
				ret = i;
		i++;
	}
	return (ret);
}

static int		find_first_not_command_line_number(t_tokens *tokens)
{
	int			i;
	int			ret;
	t_lex_list	*tmp;

	i = 0;
	ret = -1;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		if (tmp != NULL)
			if (tmp->lexem->type != COMMAND)
			{
				ret = i;
				break ;
			}
		i++;
	}
	return (ret);
}

void			get_syn_sem_errors(t_tokens *tokens, t_errors **err)
{
	int	com;
	int	code;

	code = find_first_not_command_line_number(tokens);
	com = find_last_command_line_number(tokens);
	if (com == -1)
	{
		push_back_errors_list(err, SEMANTIC, NO_COMMANDS, NULL);
		return ;
	}
	else
	{
		if (code == -1)
			push_back_errors_list(err, SEMANTIC, NO_CODE, NULL);
		else
		{
			if (code < com)
				push_back_errors_list(err, SYNTACTIC,
						WRONG_PROGRAM_STRUCTURE, NULL);
			check_code(tokens, err);
		}
		check_commands(tokens, err);
	}
}
