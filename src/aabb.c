/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:12:18 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/19 14:54:41 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	aabb(t_ray *ray, t_obj *obj)
{
	int		s[3];
	double	t[6];

	s[0] = ray->invdir.mtx[0] < 0;
	s[1] = ray->invdir.mtx[1] < 0;
	s[2] = ray->invdir.mtx[2] < 0;
	t[0] = (obj->aabb[s[0]].mtx[0] - ray->pos.mtx[0]) * ray->invdir.mtx[0];
	t[1] = (obj->aabb[1 - s[0]].mtx[0] - ray->pos.mtx[0]) * ray->invdir.mtx[0];
	t[2] = (obj->aabb[s[1]].mtx[1] - ray->pos.mtx[1]) * ray->invdir.mtx[1];
	t[3] = (obj->aabb[1 - s[1]].mtx[1] - ray->pos.mtx[1]) * ray->invdir.mtx[1];
	if (t[0] > t[3] || t[2] > t[1])
		return (0);
	t[0] = MAX(t[0], t[2]);
	t[1] = MIN(t[3], t[1]);
	t[4] = (obj->aabb[s[2]].mtx[2] - ray->pos.mtx[2]) * ray->invdir.mtx[2];
	t[5] = (obj->aabb[1 - s[2]].mtx[2] - ray->pos.mtx[2]) * ray->invdir.mtx[2];
	if (t[0] > t[5] || t[4] > t[1])
		return (0);
	t[0] = MAX(t[0], t[4]);
	t[1] = MIN(t[1], t[5]);
	return (1);
}
