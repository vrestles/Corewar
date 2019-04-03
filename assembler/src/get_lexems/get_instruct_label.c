/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruct_label_lexems.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:53:13 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/27 16:24:25 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_lexem			*get_label(char *str, t_cursor *cur, int len)
{
	t_lexem	*res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = LABEL;
	cur->pos += len + 1;
	return (res);
}

t_lexem			*get_instruction(char *str, t_cursor *cur, int len)
{
	t_lexem	*res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = INSTRUCT;
	cur->pos += len;
	return (res);
}

t_lexem			*get_direct_label(char *str, t_cursor *cur)
{
	t_lexem	*res;
	int		j;
	int		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = cur->pos + 2;
	while (str[j])
	{
		if (is_label_char(str[j]) == false)
			break ;
		j++;
	}
	len = j - cur->pos - 2;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 2, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = DIR_LABEL;
	cur->pos = j;
	return (res);
}

t_lexem			*get_indir_label(char *str, t_cursor *cur)
{
	t_lexem	*res;
	int		i;
	int		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	i = cur->pos + 1;
	while (str[i])
	{
		if (is_label_char(str[i]))
			i++;
		else
			break ;
	}
	len = i - (cur->pos + 1);
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = INDIR_LABEL;
	cur->pos += len + 1;
	return (res);
}
