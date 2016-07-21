/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 14:45:44 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	tobj->ftrans = mtx_product(tobj->trans, mtx_product(tobj->rot,
		tobj->scale));
	tobj->i_trans = mtx_invert(tobj->trans);
	tobj->i_rot = mtx_invert(tobj->rot);
	tobj->i_scale = mtx_invert(tobj->scale);
	tobj->i_ftrans = mtx_invert(tobj->ftrans);
	obj->trans = *tobj;
}
