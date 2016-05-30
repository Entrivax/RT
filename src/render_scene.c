/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:41:10 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/30 14:08:31 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb	get_pixel_color(t_env *env, int x, int y)
{
	t_rgb	color;
	t_ray	ray;
	t_list	*current;
	double	t;

	ray.dir = norm_vect(mtx_add(env->scene->camera->dir, mtx_add(mtx_mult(
		env->scene->x_indent, x), mtx_mult(env->scene->y_indent, y))));
	ray.pos = env->scene->camera.pos;
	while (current)
	{
		if ((t = find_dist(ray, (t_obj *)current->content)) > LIMIT_MIN
			&& t < ray.t)
		{
			ray.t = t;
			ray.closest = (t_obj *)current->content;
		}
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
