/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_labels_stuff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:16:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 19:18:28 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lab_list	*create_lab_list(t_lexem *content)
{
	t_lab_list	*ptr;

	ptr = (t_lab_list *)malloc(sizeof(t_lab_list));
	if (ptr == NULL)
		return (NULL);
	ptr->next = NULL;
	ptr->lexem = content;
	return (ptr);
}

void				push_back_lab_list(t_lab_list **alst, t_lexem *content)
{
	t_lab_list	*tmp;

	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = create_lab_list(content);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_lab_list(content);
}

void				delete_lab_list(t_lab_list **lab)
{
	t_lab_list	*tmp;
	t_lab_list	*del;

	if (*lab == NULL)
		return ;
	del = NULL;
	tmp = *lab;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		free(del);
		del = NULL;
	}
	*lab = NULL;
}

t_lab_list			*generate_lab_list(t_tokens *tokens)
{
	t_lab_list	*new;
	int			i;
	t_lex_list	*tmp;

	i = 0;
	new = NULL;
	while (i < tokens->count)
	{
		if ((tmp = tokens->tokenlst[i]) != NULL)
		{
			while (tmp)
			{
				if (tmp->lexem->type == LABEL)
					push_back_lab_list(&new, tmp->lexem);
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (new);
}
