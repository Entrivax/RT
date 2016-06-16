/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:41:10 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/16 15:01:59 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb	get_pixel_color(t_env *env, int x, int y)
{
	t_ray	ray;

	ray.dir = norm_vect(mtx_add(env->scene->camera->dir, mtx_add(mtx_mult(env->
		scene->camera->x_indent, x - env->scene->camera->res.width / 2), mtx_mult(
		env->scene->camera->y_indent, y - env->scene->camera->res.height / 2))));
	ray.pos = env->scene->camera->pos;
	return (find_closest(env->scene, &ray) ? compute_light(env->scene, &ray) :
		env->scene->bgcolor);
}

void			render_scene(t_env *env)
{
	int		x;
	int		y;

	x = -1;
	while (++x < env->scene->camera->res.width)
	{
		y = -1;
		while (++y < env->scene->camera->res.height)
			set_img_pixel(&env->bg_img, x, y, get_pixel_color(env, x, y));
	}
}
