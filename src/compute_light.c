/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:58 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/19 13:09:28 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_params(t_phpa *ph, t_ray *lray, t_ray *ray)
{
	ph->lray = lray;
	ph->ray = ray;
}

static void	set_ambiant_light(t_phpa *ph, t_scene *scene, t_ray *ray,
								t_rgb *color)
{
	double	dot;
	t_mtx	n;

	n = mtx_negate(ray->dir);
	dot = ft_fclamp(dot_vect(&n, &ph->normal) + scene->ambbaseimpact,
		0, 1);
	*color = rgb_new(ft_min(scene->i_ambiant.r, ray->closest->color.r) * dot
		* ray->closest->k_ambiant,
		ft_min(scene->i_ambiant.g, ray->closest->color.g) * dot
		* ray->closest->k_ambiant,
		ft_min(scene->i_ambiant.b, ray->closest->color.b) * dot
		* ray->closest->k_ambiant);
	ph->color = color;
	ph->diffuse = &color[1];
	ph->specular = &color[2];
	*ph->diffuse = rgb_new(0, 0, 0);
	*ph->specular = rgb_new(0, 0, 0);
}

static void	set_color_max(t_phpa *ph, t_obj *obj)
{
	rgb_add(ph->color, ph->diffuse->r, ph->diffuse->g, ph->diffuse->b);
	/* *ph->color = rgb_new(ft_fclamp(ph->color->r, 0, obj->color.r),
			ft_fclamp(ph->color->g, 0, obj->color.g),
			ft_fclamp(ph->color->b, 0, obj->color.b));*/
	(void)obj;
	rgb_add(ph->color, ph->specular->r, ph->specular->g, ph->specular->b);
	rgb_clamp(ph->color);
}

t_rgb		compute_light(t_scene *scene, t_ray *ray)
{
	t_list	*current;
	t_ray	lray;
	t_rgb	color[3];
	t_phpa	ph;
	
	current = scene->lights;
	ph.normal = get_normal(*ray);
	set_ambiant_light(&ph, scene, ray, color);
	while (current)
	{
		lray.pos = ((t_light *)current->content)->pos;
		lray.dir = norm_vect(mtx_add(mtx_sub(mtx_mult(ray->dir, ray->t),
			lray.pos), ray->pos));
		if (find_closest(scene, &lray) && ray->closest == lray.closest)
		{
			set_params(&ph, &lray, ray);
			ph.camera = scene->camera;
			ph.light = (t_light *)current->content;
			phong(&ph);
		}
		current = current->next;
	}
	set_color_max(&ph, ray->closest);
	return (*color);
}
