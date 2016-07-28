/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:41:10 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 14:10:56 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb	get_pixel_color(t_env *env, int x, int y)
{
	t_ray	ray;
	t_rgb	color;
	int		x_a;
	int		y_a;

	color = rgb_new(0, 0, 0);
	x_a = -1;
	ray.pos = env->scene->camera->pos;
	while (++x_a < env->scene->camera->antialiasing)
	{
		y_a = -1;
		while (++y_a < env->scene->camera->antialiasing)
		{
			ray.dir = norm_vect(mtx_add(mtx_mult(env->scene->camera->dir,
				env->scene->camera->vp_dist), mtx_add(mtx_mult(env->
				scene->camera->x_indent, x - env->scene->camera->res.width / 2.
				+ x_a / (double)env->scene->camera->antialiasing), mtx_mult(
				env->scene->camera->y_indent, y - env->scene->camera->res.height
				/ 2. + y_a / (double)env->scene->camera->antialiasing))));
			rgb_add_rgb(&color, compute_color(env, &ray, 0, 1));
		}
	}
	rgb_div(&color, POW2(env->scene->camera->antialiasing));
	return (color);
}

void			*render_scene(void *arg)
{
	int		x;
	int		y;
	t_env	*env;

	env = (t_env *)arg;
	x = -1;
	while (++x < env->scene->camera->res.width)
	{
		y = -1;
		while (++y < env->scene->camera->res.height)
			set_img_pixel(&env->bg_img, x, y, get_pixel_color(env, x, y));
	}
	return (NULL);
}
