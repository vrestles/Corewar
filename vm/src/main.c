/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/30 19:31:54 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	show_usage(void)
{
	ft_printf(COLOR_USAGE "Usage: " COLOR_NONE
		"./corewar [-dump N -v N] <champion1.cor> <...>\n");
	ft_printf("\t%-10s : "
		"Prints output from \"aff\" (Default is to hide it)\n", "-a");
	ft_printf("\t%-10s : "
		"Dumps memory after N cycles then exits\n", "-dump N");
	ft_printf("\t%-10s : "
		"Verbosity levels, can be added together to enable several\n",
		"-v N");
	ft_printf("%20s : Show only essentials\n", "- 0");
	ft_printf("%20s : Show lives\n", "- 1");
	ft_printf("%20s : Show cycles\n", "- 2");
	ft_printf("%20s : "
		"Show operations (Params are NOT litteral ...)\n", "- 4");
	ft_printf("%20s : Show deaths\n", "- 8");
	ft_printf("%20s : Show PC movements (Except for jumps)\n", "- 16");
	ft_printf("\t%-10s : "
		"Enable graphical visualization\n",
		"-s");
}

int			main(int argc, char **argv)
{
	t_env		*env;

	SECURE_MALLOC(env = ft_memalloc(sizeof(t_env)));
	if (read_args(argc, argv, env))
	{
		vm_init(env);
		if (env->visualise)
			mlx_loop(env->mlx->mlx_ptr);
		else
		{
			while (vm_check_die(env))
				vm_loop(env);
			vm_destroy(env);
		}
	}
	else
		show_usage();
	return (0);
}
