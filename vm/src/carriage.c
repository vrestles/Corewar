/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:25:58 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 16:10:04 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*create_carriage(t_env *env, t_carriage *parent, int pos)
{
	t_carriage	*new_carriage;
	int			mem_size;

	SECURE_MALLOC(new_carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage)));
	ft_lstadd(&env->carriages, ft_lstnew_ptr(new_carriage));
	new_carriage->id = ++env->last_carriage_id;
	if (parent)
	{
		mem_size = REG_NUMBER * sizeof(unsigned int);
		ft_memcpy(new_carriage->registers, parent->registers, mem_size);
		new_carriage->carry = parent->carry;
		new_carriage->last_live_cycle = parent->last_live_cycle;
		new_carriage->color = parent->color;
	}
	new_carriage->position = pos;
	env->carriages_count++;
	return (new_carriage);
}

t_list		*remove_carriage(t_env *env, t_list *die_carriage)
{
	t_list	*cur_lst;
	t_list	*next;

	next = die_carriage->next;
	if (env->carriages == die_carriage)
		env->carriages = env->carriages->next;
	else
	{
		cur_lst = env->carriages;
		while (cur_lst && cur_lst->next)
		{
			if (cur_lst->next == die_carriage)
			{
				cur_lst->next = die_carriage->next;
				break ;
			}
			cur_lst = cur_lst->next;
		}
	}
	free(die_carriage->content);
	free(die_carriage);
	env->carriages_count--;
	return (next);
}
