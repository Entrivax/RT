/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:23:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/20 15:11:27 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

t_mtx	get_normal(t_ray ray)
{
	t_mtx	pos;
	t_mtx	normal;
	t_obj	*obj;

	obj = ray.closest;
	pos = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);
	pos = mtx_product(obj->trans.ftrans, pos);
	set_vector(&normal, 2 * AX * pos.mtx[0] + EX * pos.mtx[2] + FX * pos.mtx[1]
		+ GX,
		2 * BX * pos.mtx[1] + DX * pos.mtx[2] + FX * pos.mtx[0] + HX,
		2 * CX * pos.mtx[2] + DX * pos.mtx[1] + EX * pos.mtx[0] + IX);
	return (norm_vect(normal));
}
