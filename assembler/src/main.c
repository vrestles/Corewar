/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/30 23:34:33 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_main_errors(int err)
{
	if (err == NO_FILE)
	{
		ft_putendl_fd("Usage: Enter the name of the "
				".s-file containing your champion", 1);
		exit(0);
	}
	else if (err == MORE_THAN_ONE_FILE)
	{
		ft_putendl_fd("I can interpret only one champion at the time", 1);
		exit(0);
	}
	else if (err == CANT_OPEN_FILE)
	{
		perror("Open");
		exit(1);
	}
	else if (err == EMPTY_FILE)
	{
		ft_putendl_fd("There are no information "
				"at all about champion in the file!", 2);
		exit(1);
	}
	else
		exit(1);
}

static void		print_errors_and_exit(
	char *name, t_tokens **tokens, t_errors **lex_errors)
{
	print_errors(name, *lex_errors);
	delete_tokens(*tokens);
	delete_lex_errors(lex_errors);
	exit(1);
}

static t_lines	*get_and_check_lines(int argc, char **argv, int *fd)
{
	char		*line;
	t_lines		*lines;

	lines = NULL;
	line = NULL;
	if (argc < 2)
		print_main_errors(NO_FILE);
	else if (argc > 2)
		print_main_errors(MORE_THAN_ONE_FILE);
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
		print_main_errors(CANT_OPEN_FILE);
	if (is_file_name_valid(argv[1]) == false)
		exit(1);
	lines = read_file_into_lines(*fd, &line);
	if (lines->count == 0)
		print_main_errors(EMPTY_FILE);
	return (lines);
}

int				main(int argc, char *argv[])
{
	int			fd;
	t_lines		*lines;
	t_tokens	*tokens;
	t_errors	*errors;

	lines = NULL;
	tokens = NULL;
	errors = NULL;
	lines = get_and_check_lines(argc, argv, &fd);
	tokens = get_tokens(lines);
	delete_comments(&tokens);
	delete_lines(lines);
	get_lex_errors(tokens, &errors);
	if (errors)
		print_errors_and_exit(argv[1], &tokens, &errors);
	get_syn_sem_errors(tokens, &errors);
	if (errors)
		print_errors_and_exit(argv[1], &tokens, &errors);
	delete_str_commas(tokens);
	ft_to_code(tokens, argv[1]);
	delete_tokens(tokens);
	close(fd);
	exit(0);
}
