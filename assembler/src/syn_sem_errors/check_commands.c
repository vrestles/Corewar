/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:09:28 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 20:57:23 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		not_valid_count_commands(t_tokens *tokens, t_errors **err,
									int name_count, int comment_count)
{
	if (name_count == 0)
		push_back_errors_list(err, SEMANTIC, COMMAND_NAME_NOT_FOUND, NULL);
	else if (name_count > 1)
		find_fisrt_redef_command(tokens, "name", err);
	if (comment_count == 0)
		push_back_errors_list(err, SEMANTIC, COMMAND_COMMENT_NOT_FOUND, NULL);
	else if (comment_count > 1)
		find_fisrt_redef_command(tokens, "comment", err);
}

static void		check_command_size(t_lexem *lexem, t_errors **error)
{
	if (ft_strcmp(lexem->value, "name"))
		if (ft_strlen(lexem->value) >= PROG_NAME_LENGTH)
			push_back_errors_list(error, SEMANTIC, EXCESS_SIZE_COMMAND, lexem);
	if (ft_strcmp(lexem->value, "comment"))
		if (ft_strlen(lexem->value) >= COMMENT_LENGTH)
			push_back_errors_list(error, SEMANTIC, EXCESS_SIZE_COMMAND, lexem);
}

static void		find_command_line_errors(t_lex_list *lexem_lst,
										t_errors **error)
{
	t_lex_list	*head;

	head = lexem_lst;
	if (!lexem_lst->next)
	{
		return (push_back_errors_list(error, SEMANTIC,
			NO_ARGUMENTS, lexem_lst->lexem));
	}
	lexem_lst = lexem_lst->next;
	if (lexem_lst->lexem->type != STRING)
		push_back_errors_list(error, SEMANTIC,
				INVALID_TYPE_OF_ARGUMENT, lexem_lst->lexem);
	else
		check_command_size(lexem_lst->lexem, error);
	if (lexem_lst->next)
		return (push_back_errors_list(error, SEMANTIC,
				INVALID_NUMBER_OF_ARGUMENT, head->lexem));
}

void			check_commands(t_tokens *tokens, t_errors **err)
{
	int			name_count;
	int			comment_count;
	int			i;
	t_lex_list	*tmp;

	name_count = count_command_definitions(tokens, "name");
	comment_count = count_command_definitions(tokens, "comment");
	i = 0;
	if (name_count == 0 || name_count > 1 ||
		comment_count == 0 || comment_count > 1)
	{
		not_valid_count_commands(tokens, err, name_count, comment_count);
		return ;
	}
	while (i < tokens->count)
	{
		if ((tmp = tokens->tokenlst[i]) != NULL)
		{
			if (tmp->lexem->type == COMMAND)
				find_command_line_errors(tmp, err);
		}
		i++;
	}
}
