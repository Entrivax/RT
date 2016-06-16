/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:58 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/16 15:11:12 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_params(t_phpa *ph, t_rgb *color, t_ray *lray, t_ray *ray)
{
	ph->color = color;
	ph->lray = lray;
	ph->ray = ray;
}

static void	set_ambiant_light(t_scene *scene, t_ray *ray, t_rgb *color)
{
	*color = rgb_new(ft_min(scene->i_ambiant.r, ray->closest->color.r)
		* ray->closest->k_ambiant,
		ft_min(scene->i_ambiant.g, ray->closest->color.g)
		* ray->closest->k_ambiant,
		ft_min(scene->i_ambiant.b, ray->closest->color.b)
		* ray->closest->k_ambiant);
}

t_rgb		compute_light(t_scene *scene, t_ray *ray)
{
	t_list	*current;
	t_ray	lray;
	t_rgb	color;
	t_phpa	ph;
	
	current = scene->lights;
	set_ambiant_light(scene, ray, &color);
	ph.normal = get_normal(*ray);
	while (current)
	{
		lray.pos = ((t_light *)current->content)->pos;
		lray.dir = norm_vect(mtx_sub(mtx_mult(ray->dir, ray->t), lray.pos));
		if (find_closest(scene, &lray) && ray->closest == lray.closest)
		{
			ft_putendl("found");
			set_params(&ph, &color, &lray, ray);
			ph.camera = scene->camera;
			ph.light = (t_light *)current->content;
			phong(&ph);
		}
		current = current->next;
	}
	rgb_clamp(&color);
	return (color);
}
