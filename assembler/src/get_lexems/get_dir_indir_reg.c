/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:13:44 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 18:25:55 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_lexem		*get_indir_num(char *str, t_cursor *cur)
{
	t_lexem		*res;
	int			j;
	int			len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = INDIR;
	cur->pos = j;
	return (res);
}

t_lexem		*get_register(char *str, t_cursor *cur)
{
	t_lexem		*res;
	int			j;
	int			len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = REG;
	cur->pos = j;
	return (res);
}

t_lexem		*get_direct(char *str, t_cursor *cur)
{
	t_lexem		*res;
	int			j;
	int			len;

	j = cur->pos + 1;
	if (str[j] == ':')
		return (get_direct_label(str, cur));
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = DIR;
	cur->pos = j;
	return (res);
}
