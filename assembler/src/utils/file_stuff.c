/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:31:51 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 17:59:57 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_file_extension(char *str, char c)
{
	int len;

	len = (int)ft_strlen(str);
	str += len - 1;
	while (*str)
	{
		if (*str == c)
			return (str);
		str--;
	}
	return (str);
}

t_bool			is_file_name_valid(char *str)
{
	char *ext;

	ext = get_file_extension(str, '.');
	if (ft_strcmp(".s", ext) != 0)
	{
		ft_putendl_fd("Invalid file extension!", 2);
		return (false);
	}
	return (true);
}

void			expand_lines(t_lines **lines, char *line)
{
	char	*new;
	int		count;

	new = ft_strdup(line);
	count = (*lines)->count + 1;
	(*lines)->line = (char **)realloc((*lines)->line, sizeof(char *) * count);
	(*lines)->count = count;
	(*lines)->line[count - 1] = new;
	ft_strdel(&line);
}

t_lines			*read_file_into_lines(int fd, char **line)
{
	t_lines *lines;

	lines = (t_lines *)ft_memalloc(sizeof(t_lines));
	CHECK_NULL(lines);
	while (get_next_line(fd, line) > 0)
		expand_lines(&lines, *line);
	return (lines);
}
