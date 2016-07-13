/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 14:40:00 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/13 14:44:48 by lpilotto         ###   ########.fr       */
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

	(void)ray;
	objpos = mtx_mult(mtx_product(obj->trans.i_trans, inter->pos),
		((t_cylinder *)obj)->radius);
	set_vector(&normal,
		0,
		objpos.mtx[1],
		0);
	return (norm_vect(mtx_product(obj->trans.rot, normal)));
}
