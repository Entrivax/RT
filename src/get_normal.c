/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:23:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 15:44:15 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

t_mtx	get_normal(t_ray ray)
{
	t_mtx	pos;
	t_obj	*obj;
	t_inter	inter;

	obj = ray.closest;
	pos = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);
	pos.mtx[3] = 1;
	inter.pos = pos;
	inter.t = 0;
	return (obj->normal(obj, &inter, &ray));
}
