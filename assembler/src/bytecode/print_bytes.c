/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:26:35 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/29 19:06:37 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_print_error(t_lexem *lexem)
{
	ft_putstr_fd("Error at [", 2);
	ft_putnbr_fd(lexem->line, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(lexem->start, 2);
	ft_putchar_fd(']', 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

char	*ft_print_bytes(int number, unsigned int bytes)
{
	char	*result;
	int		i;

	if (bytes == 0)
		return (NULL);
	result = ft_strnew(bytes);
	i = bytes - 1;
	while (bytes > 0)
	{
		result[i] = (unsigned char)(number & FIRST_BYTE);
		number = number >> 8;
		i--;
		bytes--;
	}
	return (result);
}

void	ft_write_program(char **program, unsigned int *bytes,
		unsigned int size, int code)
{
	char	*tmp;
	int		i;

	*program = (char *)realloc(*program, sizeof(char) * (*bytes + size + 1));
	tmp = *program;
	i = *bytes + size - 1;
	while (size > 0)
	{
		tmp[i] = (unsigned char)(code & FIRST_BYTE);
		code = code >> 8;
		i--;
		size--;
		(*bytes)++;
	}
	*bytes = *bytes + size;
}
