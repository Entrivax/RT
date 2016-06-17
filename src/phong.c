/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:41:32 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/16 16:26:04 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		phong(t_phpa *ph)
{
	t_obj	*obj;
	double	dln;
	double	dotrv;
	t_ray	inv[2];
	t_mtx	r;
	
	inv[0] = invert_ray(*ph->lray);
	obj = ph->ray->closest;
	dln = dot_vect(&inv[0].dir, &ph->normal);
	r = mtx_sub(mtx_mult(ph->normal, 2 * dln), inv[0].dir);
	inv[1] = invert_ray(*ph->ray);
	dotrv = pow(dot_vect(&r, &inv[1].dir), obj->shine);
	rgb_add(ph->color, ft_max(ph->light->color.r * obj->color.r * obj->k_diffuse * dln, 0),
		ft_max(ph->light->color.g * obj->color.g * obj->k_diffuse * dln, 0),
		ft_max(ph->light->color.b * obj->color.b * obj->k_diffuse * dln, 0));
	rgb_add(ph->color, ft_max(ph->light->color.r * obj->color.r * obj->k_spec * dotrv, 0),
		ft_max(ph->light->color.g * obj->color.g * obj->k_spec * dotrv, 0),
		ft_max(ph->light->color.b * obj->color.b * obj->k_spec * dotrv, 0));
}
