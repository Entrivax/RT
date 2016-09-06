/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:58 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/06 14:53:32 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_params(t_phpa *ph, t_ray *lray, t_ray *ray)
{
	ph->lray = lray;
	ph->ray = ray;
}

static char	near_enough(t_ray *r1, t_ray *r2)
{
	t_mtx	p1;
	t_mtx	p2;

	p1 = mtx_add(mtx_mult(r1->dir, r1->t), r1->pos);
	p2 = mtx_add(mtx_mult(r2->dir, r2->t), r2->pos);
	return (NEAR(p1.mtx[0], p2.mtx[0])
		&& NEAR(p1.mtx[1], p2.mtx[1])
		&& NEAR(p1.mtx[2], p2.mtx[2]));
}

static void	set_ambiant_light(t_phpa *ph, t_scene *scene, t_ray *ray,
								t_color *color)
{
	double	dot;
	t_mtx	n;

	n = mtx_negate(ray->dir);
	dot = ft_fclamp((dot_vect(&n, &ph->normal) + scene->ambbaseimpact)
		* scene->ambcoefimpact, 0, 1);
	*color = rgb_new(
		ft_min(scene->i_ambiant.r, ray->closest->mat->color.r) * dot
		* ray->closest->mat->k_ambiant,
		ft_min(scene->i_ambiant.g, ray->closest->mat->color.g) * dot
		* ray->closest->mat->k_ambiant,
		ft_min(scene->i_ambiant.b, ray->closest->mat->color.b) * dot
		* ray->closest->mat->k_ambiant);
	ph->color = color;
	ph->diffuse = &color[1];
	ph->specular = &color[2];
	*ph->diffuse = rgb_new(0, 0, 0);
	*ph->specular = rgb_new(0, 0, 0);
}

static void	set_color_max(t_phpa *ph)
{
	rgb_add(ph->color, ph->diffuse->r, ph->diffuse->g, ph->diffuse->b);
	rgb_add(ph->color, ph->specular->r, ph->specular->g, ph->specular->b);
	rgb_clamp(ph->color);
}

t_color		compute_light(t_scene *scene, t_ray *ray)
{
	t_list	*current;
	t_ray	lray;
	t_color	color[3];
	t_phpa	ph;

	current = scene->lights;
	ph.normal = get_normal(*ray);
	set_ambiant_light(&ph, scene, ray, color);
	while (current)
	{
		lray.pos = ((t_light *)current->content)->pos;
		lray.dir = norm_vect(mtx_add(mtx_sub(mtx_mult(ray->dir, ray->t),
			lray.pos), ray->pos));
		if (find_closest(scene, &lray) && ray->closest == lray.closest
			&& near_enough(ray, &lray))
		{
			set_params(&ph, &lray, ray);
			ph.camera = scene->camera;
			ph.light = (t_light *)current->content;
			phong(&ph);
		}
		current = current->next;
	}
	set_color_max(&ph);
	return (*color);
}
