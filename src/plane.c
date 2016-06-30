/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 14:40:00 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/30 14:45:19 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cone_inter(t_obj *obj, t_ray ray)
{
	ray.pos = mtx_mult(ray.pos, obj->tobj.i_ftrans);
	ray.dir = mtx_mult(ray.dir, obj->i_rot);
	return (-(ray.pos.y + 1 / ray.dir.y));
}
