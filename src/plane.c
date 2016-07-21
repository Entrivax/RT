/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 14:40:00 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 15:34:57 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	plane_inter(t_obj *obj, t_ray ray)
{
	ray.pos = mtx_product(obj->trans.i_ftrans, ray.pos);
	ray.dir = mtx_product(obj->trans.i_rot, ray.dir);
	return (-(ray.pos.mtx[1] / ray.dir.mtx[1]));
}

t_mtx	plane_normal(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_mtx	normal;
	t_mtx	objpos;

	(void)inter;
	objpos = mtx_product(obj->trans.i_rot, mtx_product(obj->trans.i_trans,
		ray->pos));
	set_vector(&normal,
		0,
		objpos.mtx[1],
		0);
	normal = mtx_product(obj->trans.rot, normal);
	return (norm_vect(normal));
}
