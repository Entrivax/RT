/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:23:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/20 15:52:48 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

#include <stdio.h>
t_mtx	get_normal(t_ray ray)
{
	t_mtx	pos;
//	t_mtx	normal;
	t_obj	*obj;
	t_inter	inter;

	obj = ray.closest;
	pos = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);
	pos.mtx[3] = 1;
	//pos = mtx_product(obj->trans.i_trans, pos);
	inter.pos = pos;
	inter.t = 0;
	return (obj->normal(obj, &inter, &ray));
	/*
	//pos = mtx_product(obj->trans.ftrans, pos);
	//printf("Object's position: (%lf; %lf; %lf)\n", pos.mtx[0], pos.mtx[1], pos.mtx[2]);
	set_vector(&normal, 2 * AX * pos.mtx[0] + EX * pos.mtx[2] + FX * pos.mtx[1]
		+ GX,
		2 * BX * pos.mtx[1] + DX * pos.mtx[2] + FX * pos.mtx[0] + HX,
		2 * CX * pos.mtx[2] + DX * pos.mtx[1] + EX * pos.mtx[0] + IX);
	normal = norm_vect(normal);
	return (mtx_product(obj->trans.rot, normal));*/
}
