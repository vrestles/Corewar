/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_code.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:51:36 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/30 23:35:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*ft_get_extension(char *str, char c)
{
	int	len;

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

static char		*ft_correct_name(char *name)
{
	size_t	size;
	char	*cor;

	size = ft_strlen(name);
	cor = ft_strnew(size + 2);
	ft_strcpy(cor, name);
	ft_strcpy(ft_get_extension(cor, '.'), ".cor");
	return (cor);
}

static void		ft_write_to_file(int fd, t_header *head, char *program)
{
	char	*magic;
	char	*size;
	char	*null;

	null = ft_print_bytes(0, 4);
	magic = ft_print_bytes(head->magic, 4);
	write(fd, magic, 4);
	ft_strdel(&magic);
	write(fd, head->prog_name, PROG_NAME_LENGTH);
	write(fd, null, 4);
	size = ft_print_bytes(head->prog_size, 4);
	write(fd, size, 4);
	ft_strdel(&size);
	write(fd, head->comment, COMMENT_LENGTH);
	write(fd, null, 4);
	write(fd, program, head->prog_size);
	ft_strdel(&null);
}

void			ft_to_code(t_tokens *tokens, char *name)
{
	t_header	head;
	int			line_program;
	char		*program;
	char		*file_name;
	int			fd;

	program = NULL;
	head.magic = COREWAR_EXEC_MAGIC;
	line_program = ft_set_name_comment(tokens, &head);
	head.prog_size = ft_set_program(tokens, &program, line_program);
	file_name = ft_correct_name(name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	ft_write_to_file(fd, &head, program);
	ft_printf("Writing output program to %s\n", file_name);
	ft_strdel(&program);
	ft_strdel(&file_name);
	close(fd);
}
