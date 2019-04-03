/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:28:26 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/28 19:41:55 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_lexem			*check_label_or_undef(char *str, t_cursor *cur)
{
	int i;

	i = cur->pos + 1;
	while (str[i])
	{
		if (is_label_char(str[i]))
			i++;
		else if (str[i] == LABEL_CHAR)
			return (get_label(str, cur, i - cur->pos));
		else
			break ;
	}
	i = cur->pos + 1;
	while (str[i])
	{
		if (is_undefined(str[i]))
			i++;
		else
			return (get_undef(str, cur));
	}
	return (get_undef(str, cur));
}

t_lexem			*check_instuct_label_reg(char *str, t_cursor *cur)
{
	int i;

	i = cur->pos + 1;
	if (str[cur->pos] == 'r')
		if (str[i] && (ft_isdigit(str[i]) || is_digit_sign(str[i])))
			return (get_register(str, cur));
	i = cur->pos + 1;
	while (str[i])
	{
		if (is_label_char(str[i]))
			i++;
		else if (str[i] == LABEL_CHAR)
			return (get_label(str, cur, i - cur->pos));
		else
			break ;
	}
	return (get_instruction(str, cur, i - cur->pos));
}

t_lexem			*check_indir_or_label(char *str, t_cursor *cur)
{
	int i;

	i = cur->pos + 1;
	while (str[i])
	{
		if (is_label_char(str[i]))
			i++;
		else if (str[i] == LABEL_CHAR)
			return (get_label(str, cur, i - cur->pos));
		else
			break ;
	}
	i = cur->pos + 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (get_indir_num(str, cur));
	}
	return (get_indir_num(str, cur));
}
