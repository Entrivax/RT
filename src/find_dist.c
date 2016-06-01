/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:09:33 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/01 15:36:01 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_dist(t_ray ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	int		ret;
	t_mtx	mtxs[2];

	mtxs[0] = mtx_dotproduct(obj->mtx, ray.dir);
	mtxs[1] = mtx_dotproduct(obj->mtx, ray.pos);
	abc[0] = mtx_dot(ray.dir, mtxs[0], 0, 0);
	abc[1] = 2 * mtx_dot(ray.dir, mtxs[1], 0, 0);
	abc[2] = mtx_dot(ray.pos, mtxs[1], 0, 0);
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
