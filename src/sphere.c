/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 12:29:02 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/13 17:29:18 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	sphere_inter(t_obj *obj, t_ray ray)
{
	double	abc[3];
	char	ret;
	double	t[2];
	double	h;

	ray.pos = mtx_product(obj->trans.i_ftrans, ray.pos);
	ray.dir = mtx_product(obj->trans.i_rot, ray.dir);
	abc[0] = POW2(ray.dir.mtx[0]) + POW2(ray.dir.mtx[1]) + POW2(ray.dir.mtx[2]);
	abc[1] = 2 * (ray.pos.mtx[0] * ray.dir.mtx[0]
		+ ray.pos.mtx[1] * ray.dir.mtx[1] + ray.pos.mtx[2] * ray.dir.mtx[2]);
	abc[2] = POW2(ray.pos.mtx[0]) + POW2(ray.pos.mtx[1]) + POW2(ray.pos.mtx[2])
		- ((t_sphere *)obj)->radius;
	if ((ret = solve_quadratic(abc, t)) == 0)
		return (-1);
	if ((h = ray.dir.mtx[1] * t[0] + ray.pos.mtx[1])
		>= ((t_cone *)obj)->h1 && h <= ((t_sphere *)obj)->h2)
		return (t[0]);
	else if ((h = ray.dir.mtx[1] * t[1] + ray.pos.mtx[1])
		>= ((t_cone *)obj)->h1 && h <= ((t_sphere *)obj)->h2)
		return (t[1]);
	return (-1);
}

t_mtx	sphere_normal(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_mtx	normal;
	t_mtx	objpos;
	t_mtx	roriobj;

	objpos = mtx_mult(mtx_product(obj->trans.i_trans, inter->pos),
		1 / ((t_sphere *)obj)->radius);
	roriobj = mtx_mult(mtx_product(obj->trans.i_rot,
		mtx_product(obj->trans.i_trans, ray->pos)),
			1 / ((t_sphere *)obj)->radius);
	set_vector(&normal,
		objpos.mtx[0],
		objpos.mtx[1],
		objpos.mtx[2]);
	if (sqrt(POW2(roriobj.mtx[0]) + POW2(roriobj.mtx[1])
		+ POW2(roriobj.mtx[2])) < 1)
		normal = mtx_negate(normal);
	return (norm_vect(normal));
}
