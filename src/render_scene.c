/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:41:10 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/25 18:19:07 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb	get_pixel_color(t_env *env, int x, int y)
{
	t_rgb	color;
	t_ray	ray;
	t_list	*current;

	ray.dir = norm_vect(mtx_add(env->scene->camera->dir, mtx_add(mtx_mult(
		env->scene->x_indent, x), mtx_mult(env->scene->y_indent, y))));
	ray.pos = env->scene->camera.pos;
	while (current)
	{
		current = current->next;
	}
	return (color);
}

void			render_scene(t_env *env)
{
	int		x;
	int		y;

	x = -1;
	while (++x < env->scene->camera->width)
	{
		y = -1;
		while (++y < env->scene->camera->height)
			set_img_pixel(&env.img, x, y, get_pixel_color(env, x, y));
	}
}
