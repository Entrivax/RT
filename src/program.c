/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:04:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/27 13:42:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	print_usage(char *binary_name)
{
	ft_putendl("Usage: ");
	ft_putstr(binary_name);
	ft_putendl(" <scene_file>");
}

void		program(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
	{
		if (argc > 0)
			print_usage(argv[0]);
		exit(0);
	}
	if ((env = init_env()) == NULL)
		exit(-1);
	if (parse_file(env, argv[1]) == -1)
		exit(-1);
	set_mlx_hooks(env);
	render_scene(env);
	mlx_loop(env->mlx);
}
