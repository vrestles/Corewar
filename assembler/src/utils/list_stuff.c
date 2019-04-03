/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:14:42 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 21:33:31 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lex_list	*create_lex_list(t_lexem *content)
{
	t_lex_list	*ptr;

	ptr = (t_lex_list *)malloc(sizeof(t_lex_list));
	if (ptr == NULL)
		return (NULL);
	ptr->next = NULL;
	ptr->lexem = content;
	return (ptr);
}

void				push_back_lex_list(t_lex_list **alst, t_lexem *content)
{
	t_lex_list	*tmp;

	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = create_lex_list(content);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_lex_list(content);
}

static t_errors		*create_lex_errors(int err, int addit_err,
											t_lexem *lexem)
{
	t_errors	*ptr;

	ptr = (t_errors *)malloc(sizeof(t_errors));
	if (ptr == NULL)
		return (NULL);
	ptr->next = NULL;
	ptr->error_code[0] = err;
	ptr->error_code[1] = addit_err;
	ptr->lexem = lexem;
	return (ptr);
}

void				push_back_errors_list(t_errors **alst, int err,
									int addit_err, t_lexem *lexem)
{
	t_errors	*tmp;

	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = create_lex_errors(err, addit_err, lexem);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_lex_errors(err, addit_err, lexem);
}

void				delete_elem_lex_list(t_lex_list **lst, t_lex_list *del)
{
	t_lex_list	*tmp;

	tmp = NULL;
	if (*lst == NULL || del == NULL)
		return ;
	if (*lst == del)
		*lst = del->next;
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->next == del)
			{
				tmp->next = del->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	delete_lexem(&(del->lexem));
	free(del);
	del = NULL;
}
