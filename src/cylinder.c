/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 14:12:54 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/30 14:14:24 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cylinder_inter(t_obj *obj, t_ray ray)
{
	double	abc[3];
	double	t[2];

	ray.pos = mtx_mult(ray.pos, obj->tobj.i_ftrans);
	ray.dir = mtx_mult(ray.dir, obj->i_rot);
	abc[0] = POW2(ray.dir.x) + POW2(ray.dir.z);
	abc[1] = 2 * (ray.pos.x * ray.dir.x + ray.pos.z * ray.dir.z);
	abc[2] = POW2(ray.pos.x) + POW2(ray.pos.z) - 1;
	if ((ret = solve_quadratic(abc, t, t + 1)) == 0)
		return (-1);
	if (ret == 1)
		return (t[0]);
	if ((t[0] < t[1] || t[1] <= LIMIT_MIN) && t[0] > LIMIT_MIN)
		return (t[0]);
	else if (t[1] > LIMIT_MIN)
		return (t[1]);
	return (-1);
}
