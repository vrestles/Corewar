/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:21:12 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/29 13:37:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			read_exec_code(int fd, t_champion *champion)
{
	int				i;
	unsigned char	read_null;

	i = 0;
	if (champion->prog_size > CHAMP_MAX_SIZE)
		throw_error(STR_ERROR_VALID,
			"exec code champion more than CHAMP_MAX_SIZE");
	else if (!champion->prog_size)
		throw_error(STR_ERROR_VALID,
			"is too small to be a champion");
	SECURE_MALLOC(champion->exec_code = (unsigned char*)
		ft_memalloc(sizeof(unsigned char) * champion->prog_size));
	while (i < (int)champion->prog_size)
	{
		if (read(fd, champion->exec_code, 1) == 0)
			throw_error(STR_ERROR_VALID, "error exec code");
		champion->exec_code++;
		i++;
	}
	if (read(fd, &read_null, sizeof(read_null)))
		throw_error(STR_ERROR_VALID, "error size exec code");
	champion->exec_code -= champion->prog_size;
}

static t_champion	*read_champion(char *filename)
{
	int				magic_header;
	t_champion		*champion;
	unsigned int	read_null;
	int				fd;

	fd = open(filename, O_RDONLY);
	read(fd, &magic_header, sizeof(int));
	swap_bytes(&magic_header, sizeof(magic_header));
	if (magic_header != COREWAR_EXEC_MAGIC)
		throw_error(STR_ERROR_VALID, "error magic header");
	SECURE_MALLOC(champion = (t_champion*)malloc(sizeof(t_champion)));
	read(fd, &champion->prog_name, PROG_NAME_LENGTH);
	champion->prog_name[PROG_NAME_LENGTH] = '\0';
	read(fd, &read_null, sizeof(read_null));
	if (read_null)
		throw_error(STR_ERROR_VALID, "error NULL 1");
	read(fd, &champion->prog_size, sizeof(champion->prog_size));
	swap_bytes(&champion->prog_size, sizeof(champion->prog_size));
	read(fd, &champion->comment, COMMENT_LENGTH);
	champion->comment[COMMENT_LENGTH] = '\0';
	read(fd, &read_null, sizeof(read_null));
	if (read_null)
		throw_error(STR_ERROR_VALID, "error NULL 2");
	read_exec_code(fd, champion);
	return (champion);
}

void				put_champ_on_arr(int nbr_player,
	char *argv, t_env *env, int *mask)
{
	int i;

	if (nbr_player)
		env->champions[nbr_player - 1] = read_champion(argv);
	else
	{
		i = 0;
		while (mask[i] != 0)
			i++;
		mask[i] = 1;
		env->champions[i] = read_champion(argv);
	}
}

void				check_arr_champions(int count_champion, int *mask)
{
	int i;

	i = 0;
	if (count_champion > MAX_PLAYERS)
		throw_error(STR_ERROR_READ, "Incorrect count players");
	while (i < count_champion)
	{
		if (mask[i] == 0)
			throw_error(STR_ERROR_READ, "Incorrect position players");
		i++;
	}
}
