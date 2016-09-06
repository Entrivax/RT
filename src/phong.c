/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:41:32 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/12 15:25:53 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			phong(t_phpa *ph)
{
	t_obj	*obj;
	double	d[2];
	double	p;
	t_ray	inv[2];
	t_mtx	r;

	p = ph->light->power / POW2(ph->lray->t);
	inv[0] = invert_ray(*ph->lray);
	inv[1] = invert_ray(*ph->ray);
	obj = ph->ray->closest;
	d[0] = ft_max(DOTV(ph->normal, inv[0].dir), 0.0);
	r = vect_reflect(inv[0].dir, ph->normal);
	d[1] = ft_max(pow(DOTV(r, inv[1].dir), obj->mat->shine), 0.0);
	rgb_add(ph->diffuse,
		ft_max(ph->light->color.r * obj->mat->color.r *
			obj->mat->k_diffuse * d[0] * p, 0),
		ft_max(ph->light->color.g * obj->mat->color.g *
			obj->mat->k_diffuse * d[0] * p, 0),
		ft_max(ph->light->color.b * obj->mat->color.b *
			obj->mat->k_diffuse * d[0] * p, 0));
	rgb_add(ph->specular,
		ft_max(ph->light->color.r * obj->mat->k_spec * d[1] * p, 0),
		ft_max(ph->light->color.g * obj->mat->k_spec * d[1] * p, 0),
		ft_max(ph->light->color.b * obj->mat->k_spec * d[1] * p, 0));
}
