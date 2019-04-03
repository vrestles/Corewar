/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:23:39 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 15:29:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_check_comment(t_header *head, t_lex_list *list, int *comment)
{
	char *str;

	str = NULL;
	if (list->next != NULL && list->next->lexem->type != STRING)
		ft_print_error(list->next->lexem);
	else
		str = list->next->lexem->value;
	if (list->next->next == NULL)
	{
		if (ft_strlen(str) <= COMMENT_LENGTH)
		{
			*comment = 1;
			ft_strcpy(head->comment, str);
		}
		else
		{
			perror("COMMENT TOO BIG!");
			exit(1);
		}
	}
	else
		ft_print_error(list->next->next->lexem);
}

static void	ft_check_name(t_header *head, t_lex_list *list, int *name)
{
	char *str;

	str = NULL;
	if (list->next != NULL && list->next->lexem->type != STRING)
		ft_print_error(list->next->lexem);
	else
		str = list->next->lexem->value;
	if (list->next->next == NULL || list->next->next->lexem->type == COMMENT)
	{
		if (ft_strlen(str) <= PROG_NAME_LENGTH)
		{
			*name = 1;
			ft_strcpy(head->prog_name, str);
		}
		else
		{
			perror("NAME TOO BIG!");
			exit(1);
		}
	}
	else
		ft_print_error(list->next->next->lexem);
}

static void	ft_check_command(t_lex_list *tmp, t_header *head,
		int *name, int *comment)
{
	if (ft_strcmp(tmp->lexem->value, "name") == 0 && *name == 1)
		ft_print_error(tmp->lexem);
	if (ft_strcmp(tmp->lexem->value, "comment") == 0 && *comment == 1)
		ft_print_error(tmp->lexem);
	if (ft_strcmp(tmp->lexem->value, "name") == 0)
		ft_check_name(head, tmp, name);
	else if (ft_strcmp(tmp->lexem->value, "comment") == 0)
		ft_check_comment(head, tmp, comment);
}

int			ft_set_name_comment(t_tokens *tokens, t_header *head)
{
	int	i;
	int	name;
	int	comment;

	name = 0;
	comment = 0;
	ft_memset(head->prog_name, 0, PROG_NAME_LENGTH + 1);
	ft_memset(head->comment, 0, COMMENT_LENGTH + 1);
	i = 0;
	while (i < tokens->count)
	{
		if (tokens->tokenlst[i] == NULL ||
			tokens->tokenlst[i]->lexem->type == COMMENT)
			;
		else if (tokens->tokenlst[i]->lexem->type != COMMAND &&
			(name == 0 || comment == 0))
			ft_print_error(tokens->tokenlst[i]->lexem);
		else if (tokens->tokenlst[i]->lexem->type == COMMAND)
			ft_check_command(tokens->tokenlst[i], head, &name, &comment);
		else if (tokens->tokenlst[i]->lexem->type != COMMAND && name == 1 &&
		comment == 1)
			break ;
		i++;
	}
	return (i);
}
