/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 15:25:28 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		cw_atoi(const char *str, const char *error)
{
	int			i;
	long long	nb;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			throw_error(STR_ERROR_READ, error);
		nb = nb * 10 + (str[i] - '0');
		if (nb > 2147483647)
			throw_error(STR_ERROR_READ, error);
		i++;
	}
	return (nb);
}

void	swap_bytes(void *memory, int size)
{
	int				i;
	unsigned char	tmp;
	unsigned char	*byte;

	byte = (unsigned char*)memory;
	i = 0;
	while (i < size / 2)
	{
		tmp = byte[i];
		byte[i] = byte[size - i - 1];
		byte[size - i - 1] = tmp;
		i++;
	}
}
