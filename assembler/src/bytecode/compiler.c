/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:27:14 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 15:32:11 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			(*g_instruct[16])(t_lex_list *args, unsigned int *bytes,
		t_list_label **labels, char **program);

static void		ft_check_instruct(t_lex_list *list, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	int index;

	g_instruct[0] = ft_live;
	g_instruct[1] = ft_ld;
	g_instruct[2] = ft_st;
	g_instruct[3] = ft_add;
	g_instruct[4] = ft_sub;
	g_instruct[5] = ft_and;
	g_instruct[6] = ft_or;
	g_instruct[7] = ft_xor;
	g_instruct[8] = ft_zjmp;
	g_instruct[9] = ft_ldi;
	g_instruct[10] = ft_sti;
	g_instruct[11] = ft_fork;
	g_instruct[12] = ft_lld;
	g_instruct[13] = ft_lldi;
	g_instruct[14] = ft_lfork;
	g_instruct[15] = ft_aff;
	index = ft_index(list->lexem->value);
	if (index == -1)
		ft_print_error(list->lexem);
	g_instruct[index](list->next, bytes, labels, program);
}

static void		ft_check_label(t_lex_list *list, unsigned int *bytes,
		t_list_label **labels, char **program)
{
	if (list->next == NULL || list->next->lexem->type == COMMENT)
		ft_add_label(labels, list->lexem->value, *bytes);
	else if (list->next->lexem->type == INSTRUCT)
	{
		ft_add_label(labels, list->lexem->value, *bytes);
		ft_check_instruct(list->next, bytes, labels, program);
	}
	else
		ft_print_error(list->next->lexem);
}

static void		ft_substitute_labels(t_list_label *labels, char *program)
{
	t_asm_list	*tmp;
	char		*sub;

	while (labels != NULL)
	{
		tmp = labels->label->idxs;
		while (tmp != NULL)
		{
			if (labels->label->start_byte == -1)
			{
				ft_putstr_fd("NO SUCH LABEL: ", 2);
				ft_putendl_fd(labels->label->name, 2);
				exit(1);
			}
			sub = ft_print_bytes(labels->label->start_byte - tmp->start,
					tmp->size);
			ft_memcpy(program + tmp->index, sub, tmp->size);
			ft_strdel(&sub);
			tmp = tmp->next;
		}
		labels = labels->next;
	}
}

void			ft_delete_lab(t_label *label)
{
	t_asm_list	*list;
	t_asm_list	*del;

	ft_strdel(&label->name);
	list = label->idxs;
	while (list != NULL)
	{
		del = list;
		list = list->next;
		free(del);
	}
	free(label);
}

unsigned int	ft_set_program(t_tokens *tokens, char **program, int start)
{
	unsigned int	bytes;
	int				i;
	t_list_label	*labels;

	labels = NULL;
	bytes = 0;
	i = start;
	while (i < tokens->count)
	{
		if (tokens->tokenlst[i] == NULL ||
		tokens->tokenlst[i]->lexem->type == COMMENT)
			;
		else if (tokens->tokenlst[i]->lexem->type == LABEL)
			ft_check_label(tokens->tokenlst[i], &bytes, &labels, program);
		else if (tokens->tokenlst[i]->lexem->type == INSTRUCT)
			ft_check_instruct(tokens->tokenlst[i], &bytes, &labels, program);
		else
			ft_print_error(tokens->tokenlst[i]->lexem);
		i++;
	}
	ft_substitute_labels(labels, *program);
	ft_delete_labels(&labels);
	return (bytes);
}
