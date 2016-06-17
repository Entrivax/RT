/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:23:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/17 12:33:48 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

t_mtx	get_normal(t_ray ray)
{
	t_mtx	pos;
	t_mtx	normal;
	t_obj	*obj;
	t_mtx	mtxs[2];

	obj = ray.closest;
	mtxs[0] = mtx_product(obj->i_trans, ray.pos);
	mtxs[1] = mtx_product(obj->i_trans, ray.dir);
	pos = mtx_add(mtx_mult(mtxs[1], ray.t), mtxs[0]);
	set_vector(&normal, 2 * AX * pos.mtx[0] + DX * pos.mtx[1] + EX * pos.mtx[2]
		+ GX,
		2 * BX * pos.mtx[1] + DX * pos.mtx[0] + FX * pos.mtx[2] + HX,
		2 * CX * pos.mtx[2] + EX * pos.mtx[0] + FX * pos.mtx[1] + IX);
	return (norm_vect(normal));
}
