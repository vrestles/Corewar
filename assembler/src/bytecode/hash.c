/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:43:45 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/29 19:06:37 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	ft_hash_func(char *name)
{
	int sum;

	sum = 0;
	if (*name == 'f')
		sum = 1;
	while (*name)
	{
		sum += *name;
		name++;
	}
	return ((char)(sum % 127));
}

int			ft_index(char *name)
{
	char	*hash_table;
	char	value;
	int		i;

	hash_table = ft_strdup("3Qh+L5b[D;R6>(\"/");
	i = 0;
	value = ft_hash_func(name);
	while (hash_table[i] != '\0')
	{
		if (hash_table[i] == value)
		{
			ft_strdel(&hash_table);
			return (i);
		}
		i++;
	}
	ft_strdel(&hash_table);
	return (-1);
}
