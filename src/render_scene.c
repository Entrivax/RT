/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:41:10 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/13 17:54:40 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb	get_pixel_color(t_env *env, int x, int y)
{
	t_rgb	color;
	t_ray	ray;
	t_list	*current;
	double	t;

	ray.dir = norm_vect(mtx_add(env->scene->camera->dir, mtx_add(mtx_mult(env->
		scene->camera->x_indent, x - env->scene->camera->res.width / 2), mtx_mult(
		env->scene->camera->y_indent, y - env->scene->camera->res.height / 2))));
	ray.pos = env->scene->camera->pos;
	ray.closest = NULL;
	current = env->scene->objects;
	if (x == env->scene->camera->res.width / 2 && y == env->scene->camera->res.height / 2)
		ft_putendl("middle of screen breakpoint");
	while (current)
	{
		if ((t = find_dist(ray, (t_obj *)current->content)) > LIMIT_MIN
			&& (t < ray.t || ray.closest == NULL))
		{
			ray.t = t;
			ray.closest = (t_obj *)current->content;
		}
		current = current->next;
	}
	color = ray.closest != NULL ? ray.closest->color : env->scene->bgcolor;
	return (color);
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
