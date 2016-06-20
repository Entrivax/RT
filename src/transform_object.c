/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/20 13:37:51 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	/*obj->trans = mtx_product(mtx_product(tobj->scale, tobj->trans),
		tobj->rot);*/
	tobj->ftrans = mtx_product(tobj->trans, mtx_product(tobj->rot,
		tobj->scale));
	tobj->i_ftrans = mtx_invert(tobj->ftrans);
	tobj->rotxscale = mtx_product(tobj->rot, tobj->scale);
	tobj->i_rotxscale = mtx_invert(tobj->rotxscale);
	tobj->i_trans = mtx_invert(tobj->trans);
	tobj->i_rot = mtx_invert(tobj->rot);
	tobj->i_scale = mtx_invert(tobj->scale);
	obj->trans = *tobj;
	//obj->mtx = mtx_product(mtx_product(obj->i_trans, obj->mtx), mtx_trans(obj->i_trans));
}
