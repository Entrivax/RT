/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:04:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/28 14:50:20 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	print_usage(char *binary_name)
{
	ft_putendl("Usage: ");
	ft_putstr(binary_name);
	ft_putendl(" [options] <scene_file>\n");
	ft_putendl("\t-t [n]\tUse n threads to compute the image");
}

int			start_working_threads(t_env *env)
{
	pthread_t	*pth;
	int			i;

	if ((pth = ft_memalloc(env->n_threads * sizeof(pthread_t))) == NULL)
		return (return_print("Error during malloc of pthread_t", -1));
	i = -1;
	if (pthread_mutex_init(&env->mutex, NULL))
		return (return_print("Error initializing the mutex", -1));
	env->processed_pixels = 0;
	while (++i < env->n_threads)
	{
		if (pthread_create(&pth[i], NULL, render_scene, env) == 0)
		{
			ft_putstr("Thread #");
			ft_putnbr(i + 1);
			ft_putendl(" started!");
		}
		else
		{
			ft_putstr("Failed to create thread #");
			ft_putnbr(i + 1);
			ft_putendl("!");
		}
	}
	return (0);
}

void		program(int argc, char **argv)
{
	t_env		*env;

	if (argc < 2)
	{
		if (argc > 0)
			print_usage(argv[0]);
		exit(0);
	}
	if ((env = init_env()) == NULL)
		exit(-1);
	if (parse_args(env, argc, argv) == -1)
		exit(-1);
	if (init_img(env->mlx, &env->bg_img, env->scene->camera->res.width,
		env->scene->camera->res.height) == -1)
		exit(-1);
	if (start_working_threads(env) == -1)
		exit(-1);
	init_win(env);
	set_mlx_hooks(env);
	mlx_loop(env->mlx);
}
