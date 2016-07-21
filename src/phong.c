/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:41:32 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 18:35:12 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mtx	reflect(t_mtx i, t_mtx n)
{
	return (mtx_sub(i, mtx_mult(n, 2 * DOTV(n, i))));
}

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
	r = reflect(inv[0].dir, ph->normal);
	d[1] = ft_max(pow(DOTV(r, inv[1].dir), obj->shine), 0.0);
	rgb_add(ph->diffuse,
	ft_max(ph->light->color.r * obj->color.r * obj->k_diffuse * d[0] * p, 0),
	ft_max(ph->light->color.g * obj->color.g * obj->k_diffuse * d[0] * p, 0),
	ft_max(ph->light->color.b * obj->color.b * obj->k_diffuse * d[0] * p, 0));
	rgb_add(ph->specular,
	ft_max(ph->light->color.r * obj->k_spec * d[1] * p, 0),
	ft_max(ph->light->color.g * obj->k_spec * d[1] * p, 0),
	ft_max(ph->light->color.b * obj->k_spec * d[1] * p, 0));
}
