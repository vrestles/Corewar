/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:37:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 11:06:23 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				print_players(t_env *env)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (env->champions[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, env->champions[i]->prog_size, env->champions[i]->prog_name,
			env->champions[i]->comment);
		i++;
	}
}

int					print_move(t_env *env, int curpos, int len)
{
	if (curpos)
		ft_printf("ADV %d (%#06x -> %#06x) ", len, curpos, curpos + len);
	else
		ft_printf("ADV %d (0x%04x -> %#06x) ", len, curpos, curpos + len);
	while (len)
	{
		ft_printf("%02x ", *(env->field + curpos % MEM_SIZE));
		curpos++;
		len--;
	}
	write(1, "\n", 1);
	return (1);
}

inline static char	get_hex_char(char octet)
{
	return ((octet < 10 ? '0' : ('a' - 10)) + octet);
}

void				print_memory(const void *memory, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (i % 64 == 0)
			i == 0 ? write(1, "0x0000 : ", 9) : ft_printf("%#06x : ", i);
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] >> 4));
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] & 0xF));
		i++;
		write(1, " ", 1);
		if (i % 64 == 0)
			write(1, "\n", 1);
	}
}
