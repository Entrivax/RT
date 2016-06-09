/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:09:33 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/09 15:39:40 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_dist(t_ray ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	int		ret;
	/*t_mtx	mtxs[2];*/
	t_mtx	v[8];

	set_vector(v,	POW2(VOM(ray.dir, 0, 0)),
					POW2(VOM(ray.dir, 1, 0)),
					POW2(VOM(ray.dir, 2, 0)));

	set_vector(v + 1,	2 * VOM(ray.dir, 0, 0) * VOM(ray.dir, 1, 0),
						2 * VOM(ray.dir, 1, 0) * VOM(ray.dir, 2, 0),
						2 * VOM(ray.dir, 0, 0) * VOM(ray.dir, 2, 0));

	set_vector(v + 2,	2 * VOM(ray.dir, 0, 0) * VOM(ray.pos, 0, 0),
						2 * VOM(ray.dir, 1, 0) * VOM(ray.pos, 1, 0),
						2 * VOM(ray.dir, 2, 0) * VOM(ray.pos, 2, 0));

	set_vector(v + 3,	2 * VOM(ray.dir, 0, 0) * VOM(ray.pos, 1, 0) + 2 * VOM(ray.pos, 0, 0) * VOM(ray.dir, 1, 0),
						2 * VOM(ray.dir, 2, 0) * VOM(ray.pos, 1, 0) + 2 * VOM(ray.pos, 2, 0) * VOM(ray.dir, 1, 0),
						2 * VOM(ray.dir, 2, 0) * VOM(ray.pos, 0, 0) + 2 * VOM(ray.pos, 2, 0) * VOM(ray.dir, 0, 0));

	v[4] = mtx_mult(ray.dir, 2);

	set_vector(v + 5,	POW2(VOM(ray.pos, 0, 0)),
						POW2(VOM(ray.pos, 1, 0)),
						POW2(VOM(ray.pos, 2, 0)));

	set_vector(v + 6,	2 * VOM(ray.pos, 0, 0) * VOM(ray.pos, 1, 0),
						2 * VOM(ray.pos, 1, 0) * VOM(ray.pos, 2, 0),
						2 * VOM(ray.pos, 0, 0) * VOM(ray.pos, 2, 0));

	v[7] = mtx_mult(ray.pos, 2);

	/*mtxs[0] = mtx_product(obj->mtx, ray.dir);
	mtxs[1] = mtx_product(obj->mtx, ray.pos);
	abc[0] = mtx_dot(mtx_trans(ray.dir), mtxs[0], 0, 0);
	abc[1] = 2 * mtx_dot(mtx_trans(ray.dir), mtxs[1], 0, 0);
	abc[2] = mtx_dot(mtx_trans(ray.pos), mtxs[1], 0, 0);*/
	abc[0] = mtx_dot(obj->mtx, v[0], 0, 0) + mtx_dot(obj->mtx, v[1], 1, 0);
	abc[1] = mtx_dot(obj->mtx, v[2], 0, 0) + mtx_dot(obj->mtx, v[3], 1, 0) + mtx_dot(obj->mtx, v[4], 2, 0);
	abc[2] = mtx_dot(obj->mtx, v[5], 0, 0) + mtx_dot(obj->mtx, v[6], 1, 0) + mtx_dot(obj->mtx, v[7], 2, 0) + VOM(obj->mtx, 3, 3);
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
