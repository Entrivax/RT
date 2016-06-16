/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:23:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/16 14:57:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

t_mtx	get_normal(t_ray ray)
{
	t_mtx	pos;
	t_mtx	normal;
	t_obj	*obj;

	pos = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);
	obj = ray.closest;
	set_vector(&normal, 2 * (AX * pos.mtx[0] + BX * pos.mtx[1] + CX * pos.mtx[2]
		+ DX),
		2 * (BX * pos.mtx[0] + EX * pos.mtx[1] + FX * pos.mtx[2] + GX),
		2 * (CX * pos.mtx[0] + FX * pos.mtx[1] + HX * pos.mtx[2] + IX));
	return (normal);
}
