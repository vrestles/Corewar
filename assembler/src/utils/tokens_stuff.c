/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:46:26 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 19:28:39 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lexem		*ft_define_lex(t_lines *lines, t_cursor *cur)
{
	if (lines->line[cur->line][cur->pos] == '.')
		return (get_command(lines->line[cur->line], cur));
	else if (lines->line[cur->line][cur->pos] == '"')
		return (get_string(lines, cur));
	else if (lines->line[cur->line][cur->pos] == COMMENT_CHAR ||
			lines->line[cur->line][cur->pos] == ALT_COMMENT_CHAR)
		return (get_comment(lines->line[cur->line], cur));
	else if (lines->line[cur->line][cur->pos] == SEPARATOR_CHAR)
		return (get_separator(lines->line[cur->line], cur));
	else if (lines->line[cur->line][cur->pos] == DIRECT_CHAR)
		return (get_direct(lines->line[cur->line], cur));
	else if (lines->line[cur->line][cur->pos] == LABEL_CHAR)
		return (get_indir_label(lines->line[cur->line], cur));
	else if (ft_isdigit(lines->line[cur->line][cur->pos]))
		return (check_indir_or_label(lines->line[cur->line], cur));
	else if (is_digit_sign(lines->line[cur->line][cur->pos]))
		return (get_indir_num(lines->line[cur->line], cur));
	else if (ft_isalpha_small(lines->line[cur->line][cur->pos]))
		return (check_instuct_label_reg(lines->line[cur->line], cur));
	else if (lines->line[cur->line][cur->pos] == '_')
		return (check_label_or_undef(lines->line[cur->line], cur));
	else
		return (get_undef(lines->line[cur->line], cur));
}

static t_lex_list	*ft_get_lex_list(t_lines *lines, t_cursor *cur, int prev)
{
	t_lex_list	*res;
	t_lexem		*new;

	res = NULL;
	while (cur->line < lines->count &&
		lines->line[cur->line] && lines->line[cur->line][cur->pos])
	{
		if (lines->line[cur->line][cur->pos] == '\t' ||
			lines->line[cur->line][cur->pos] == ' ')
			cur->pos++;
		else
		{
			if (prev < cur->line)
				break ;
			new = ft_define_lex(lines, cur);
			push_back_lex_list(&res, new);
		}
	}
	return (res);
}

t_tokens			*ft_create_empty_tokens(int count)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	CHECK_NULL(tokens);
	tokens->count = count;
	tokens->tokenlst = (t_lex_list **)malloc(sizeof(t_lex_list *) * count);
	while (i < count)
	{
		tokens->tokenlst[i] = NULL;
		i++;
	}
	return (tokens);
}

t_cursor			*ft_create_empty_cursor(void)
{
	t_cursor	*cursor;

	cursor = (t_cursor *)malloc(sizeof(t_cursor));
	CHECK_NULL(cursor);
	cursor->line = 0;
	cursor->pos = 0;
	return (cursor);
}

t_tokens			*get_tokens(t_lines *lines)
{
	int			curr_line;
	t_tokens	*res;
	t_cursor	*cursor;

	curr_line = 0;
	cursor = ft_create_empty_cursor();
	res = ft_create_empty_tokens(lines->count);
	while (curr_line < lines->count)
	{
		res->tokenlst[curr_line] = ft_get_lex_list(lines, cursor, curr_line);
		if (cursor->line > curr_line)
			curr_line = cursor->line;
		else
		{
			curr_line++;
			cursor->line++;
			cursor->pos = 0;
		}
	}
	delete_cursor(&cursor);
	return (res);
}
