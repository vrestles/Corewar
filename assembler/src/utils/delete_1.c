/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:50:51 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 21:13:21 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	delete_lex_errors(t_errors **del)
{
	t_errors *tmp;
	t_errors *cur;

	tmp = *del;
	if (*del == NULL)
		return ;
	while (tmp)
	{
		cur = tmp;
		tmp = tmp->next;
		free(cur);
		cur = NULL;
	}
	*del = NULL;
}

void	delete_lines(t_lines *del)
{
	int	i;

	i = 0;
	if (del == NULL)
		return ;
	while (i < del->count)
	{
		ft_strdel(&del->line[i]);
		i++;
	}
	free(del->line);
	free(del);
}

void	delete_lexem(t_lexem **del)
{
	char *str;

	str = (*del)->value;
	ft_strdel(&str);
	free(*del);
	(*del) = NULL;
}

void	delete_lex_list(t_lex_list **head)
{
	t_lex_list	*tmp;
	t_lex_list	*del;

	tmp = *head;
	while (tmp)
	{
		delete_lexem(&(tmp->lexem));
		del = tmp;
		tmp = tmp->next;
		free(del);
		del = NULL;
	}
	(*head) = NULL;
}

void	delete_tokens(t_tokens *del)
{
	int i;

	i = 0;
	if (del == NULL)
		return ;
	while (i < del->count)
	{
		delete_lex_list(&del->tokenlst[i]);
		i++;
	}
	free(del->tokenlst);
	free(del);
}
