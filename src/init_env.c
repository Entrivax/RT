/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:23:19 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/12 14:44:38 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_shapes_mtx(t_env *env)
{
	env->sphere_mtx = mtx_init(4, 4);
	env->sphere_mtx.mtx[0 + env->sphere_mtx.cols * 0] = 1;
	env->sphere_mtx.mtx[1 + env->sphere_mtx.cols * 1] = 1;
	env->sphere_mtx.mtx[2 + env->sphere_mtx.cols * 2] = 1;
	env->sphere_mtx.mtx[3 + env->sphere_mtx.cols * 3] = -1;
	env->plane_mtx = mtx_init(4, 4);
	env->plane_mtx.mtx[1 + env->plane_mtx.cols * 1] = 1;
	env->plane_mtx.mtx[3 + env->plane_mtx.cols * 3] = 0;
	env->cylinder_mtx = mtx_init(4, 4);
	env->cylinder_mtx.mtx[0 + env->cylinder_mtx.cols * 0] = 1;
	env->cylinder_mtx.mtx[2 + env->cylinder_mtx.cols * 2] = 1;
	env->cylinder_mtx.mtx[3 + env->cylinder_mtx.cols * 3] = -1;
	env->cone_mtx = mtx_init(4, 4);
	env->cone_mtx.mtx[0 + env->cone_mtx.cols * 0] = 1;
	env->cone_mtx.mtx[1 + env->cone_mtx.cols * 1] = 1;
	env->cone_mtx.mtx[2 + env->cone_mtx.cols * 2] = -1;
	env->cone_mtx.mtx[3 + env->cone_mtx.cols * 3] = 0;
}

t_env		*init_env(void)
{
	t_env	*env;

	if ((env = (t_env *)ft_memalloc(sizeof(t_env))) == NULL)
	{
		ft_putendl("malloc error: env");
		return (NULL);
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putendl("SDL2 init error");
		free(env);
		return (NULL);
	}
	env->n_threads = 1;
	set_shapes_mtx(env);
	init_material(&env->base_material);
	return (env);
}
