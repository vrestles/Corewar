/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_com_help_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:32:53 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 18:58:33 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_command_definitions(t_tokens *tokens, char *str)
{
	int			i;
	int			count;
	t_lex_list	*tmp;

	i = 0;
	count = 0;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		while (tmp)
		{
			if (tmp->lexem->type == COMMAND &&
				(ft_strcmp(tmp->lexem->value, str) == 0))
				count++;
			tmp = tmp->next;
		}
		i++;
	}
	return (count);
}

void		find_fisrt_redef_command(t_tokens *tokens, char *str,
									t_errors **err)
{
	int			i;
	int			count;
	t_lex_list	*tmp;

	i = -1;
	count = 0;
	while (++i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		while (tmp)
		{
			if (tmp->lexem->type == COMMAND &&
				(ft_strcmp(tmp->lexem->value, str) == 0))
			{
				if (count > 0)
					push_back_errors_list(err, SEMANTIC,
							COMMAND_REDEFINITION, tmp->lexem);
				count++;
			}
			tmp = tmp->next;
		}
	}
}
