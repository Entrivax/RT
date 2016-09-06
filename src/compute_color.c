/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:58 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/06 14:52:55 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		compute_color(t_env *env, t_ray *ray, int ref, float refrem)
{
	t_color	color;
	t_ray	reflected;
	t_mtx	normal;

	if (find_closest(env->scene, ray))
	{
		color = compute_light(env->scene, ray);
		refrem *= ray->closest->mat->refle;
		if (refrem <= 0.001 || ref >= env->scene->max_ref)
			return (color);
		normal = get_normal(*ray);
		reflected.pos = mtx_add(ray->pos, mtx_mult(ray->dir, ray->t));
		reflected.dir = vect_reflect(ray->dir, normal);
		/*rgb_mult(&color, 1 - ray->closest->refle);*/
		rgb_add_rgb(&color,
			rgb_mult_cpy(compute_color(env, &reflected, ref + 1, refrem), refrem));
		rgb_clamp(&color);
		return (color);
	}
	else
		return (env->scene->bgcolor);
}
