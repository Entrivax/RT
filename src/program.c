/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:04:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/28 19:53:21 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	run_working_threads(t_env *env)
{
	int			i;

	i = -1;
	while (++i < env->n_threads)
	{
		if (pthread_create(&env->threads[i], NULL, render_scene, env) == 0)
		{
			env->real_n_threads++;
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
}

static int	init_working_threads(t_env *env)
{
	if ((env->threads = ft_memalloc(env->n_threads *
		sizeof(pthread_t))) == NULL)
		return (return_print("Error during malloc of pthread_t", -1));
	if (pthread_mutex_init(&env->mutex, NULL))
		return (return_print("Error initializing the mutex", -1));
	env->processed_pixels = 0;
	gettimeofday(&env->clocks[0], NULL);
	run_working_threads(env);
	return (0);
}

static void	*clock_count(void *param)
{
	t_env		*env;
	int			i;

	env = (t_env *)param;
	i = -1;
	while (++i < env->n_threads)
		if (env->threads[i] != NULL)
			pthread_join(env->threads[i], NULL);
	gettimeofday(&env->clocks[1], NULL);
	ft_putstr("Time taken : ");
	ft_putnbr(env->clocks[1].tv_sec - env->clocks[0].tv_sec);
	ft_putchar(',');
	ft_putnbr((env->clocks[1].tv_usec - env->clocks[0].tv_usec) / 1000);
	ft_putendl("s");
	return (NULL);
}

static void	handle_clock(t_env *env)
{
	pthread_t	pth;

	if (pthread_create(&pth, NULL, clock_count, env))
	{
		ft_putstr("No handle of time due to the inability to run one ");
		ft_putendl("more thread, sorry.");
	}
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
	if (init_working_threads(env) == -1)
		exit(-1);
	if (env->print_time)
		handle_clock(env);
	init_win(env);
	set_mlx_hooks(env);
	mlx_loop(env->mlx);
}
