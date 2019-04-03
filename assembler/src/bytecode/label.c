/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 18:39:51 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 14:51:19 by rtroll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*ft_find_label(t_list_label *labels, char *name)
{
	int i;

	if (labels == NULL)
		return (NULL);
	i = 0;
	while (labels != NULL)
	{
		if (ft_strcmp(name, labels->label->name) == 0)
			return (labels->label);
		i++;
		labels = labels->next;
	}
	return (NULL);
}

void		ft_create_label(t_list_label **labels, char *name, int byte)
{
	t_list_label *tmp;

	tmp = *labels;
	*labels = (t_list_label*)malloc(sizeof(t_list_label));
	(*labels)->next = tmp;
	(*labels)->label = (t_label*)malloc(sizeof(t_label));
	(*labels)->label->name = ft_strdup(name);
	(*labels)->label->start_byte = byte;
	(*labels)->label->idxs = NULL;
}

static void	ft_create_substidue(t_asm_list **subs, int size, int index)
{
	t_asm_list	*tmp;

	tmp = *subs;
	*subs = (t_asm_list*)malloc(sizeof(t_asm_list));
	(*subs)->next = tmp;
	(*subs)->index = index;
	(*subs)->size = size;
}

t_label		*ft_add_2_sb(t_list_label **labels, int size,
							unsigned int index, char *name)
{
	t_label		*label;

	if ((label = ft_find_label(*labels, name)) == NULL)
	{
		ft_create_label(labels, name, -1);
		label = ft_find_label(*labels, name);
		ft_create_substidue(&(label->idxs), size, index);
	}
	else
		ft_create_substidue(&(label->idxs), size, index);
	return (label);
}

void		ft_add_label(t_list_label **labels, char *name, unsigned int byte)
{
	t_label	*label;

	if ((label = ft_find_label(*labels, name)) != NULL)
	{
		if (label->start_byte == -1)
			label->start_byte = byte;
		else
		{
			ft_putstr_fd("No same name labels allowed\n", 2);
			exit(1);
		}
	}
	else
		ft_create_label(labels, name, byte);
}
