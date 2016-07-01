/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 12:29:02 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/01 15:35:59 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cone_inter(t_obj *obj, t_ray ray)
{
	double	abc[3];
	double	t[2];
	char	ret;

	ray.pos = mtx_product(obj->trans.i_ftrans, ray.pos);
	ray.dir = mtx_product(obj->trans.i_rot, ray.dir);
	abc[0] = POW2(ray.dir.mtx[0]) - POW2(ray.dir.mtx[1]) + POW2(ray.dir.mtx[2]);
	abc[1] = 2 * (ray.pos.mtx[0] * ray.dir.mtx[0] - ray.pos.mtx[1] * ray.dir.mtx[1]
		+ ray.pos.mtx[2] * ray.dir.mtx[2]);
	abc[2] = POW2(ray.pos.mtx[0]) - POW2(ray.pos.mtx[1]) + POW2(ray.pos.mtx[2]);
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
