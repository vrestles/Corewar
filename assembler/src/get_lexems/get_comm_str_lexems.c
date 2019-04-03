/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_lexems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:50:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/27 17:56:35 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_char(t_lines *lines, t_cursor *cur, t_lexem *res, int j)
{
	char	*tmp;
	char	*new;

	tmp = NULL;
	new = NULL;
	if (lines->line[cur->line][j] == '\0')
	{
		tmp = ft_strsub(lines->line[cur->line], cur->pos, j - cur->pos);
		new = ft_strjoin(res->value, tmp);
		ft_strdel(&res->value);
		res->value = new;
		ft_strdel(&tmp);
		return (1);
	}
	if (lines->line[cur->line][j] == '"')
	{
		tmp = ft_strsub(lines->line[cur->line], cur->pos, j - cur->pos + 1);
		new = ft_strjoin(res->value, tmp);
		ft_strdel(&res->value);
		res->value = new;
		ft_strdel(&tmp);
		cur->pos = j + 1;
		return (2);
	}
	return (0);
}

t_lexem		*get_string(t_lines *lines, t_cursor *cur)
{
	t_lexem	*res;
	int		j;
	int		flag_end;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strnew(0);
	j = cur->pos + 1;
	res->start = cur->pos;
	res->line = cur->line;
	res->type = STRING;
	while (cur->line < lines->count)
	{
		while (true)
			if ((flag_end = check_char(lines, cur, res, j++)))
				break ;
		if (flag_end == 2)
			break ;
		j = 0;
		cur->pos = 0;
		cur->line++;
	}
	return (res);
}

t_lexem		*get_command(char *str, t_cursor *cur)
{
	t_lexem	*res;
	int		j;
	int		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = cur->pos + 1;
	while (str[j])
	{
		if (!ft_isalpha_small(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = COMMAND;
	cur->pos = j;
	return (res);
}

t_lexem		*get_comment(char *str, t_cursor *cur)
{
	t_lexem	*res;
	int		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	len = (int)ft_strlen(str) - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = COMMENT;
	cur->line++;
	cur->pos = 0;
	return (res);
}
