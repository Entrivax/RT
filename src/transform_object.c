/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/17 16:36:06 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	/*obj->trans = mtx_product(mtx_product(tobj->scale, tobj->trans),
		tobj->rot);*/
	obj->trans = mtx_product(tobj->trans, mtx_product(tobj->rot,
		tobj->scale));
	obj->i_trans = mtx_invert(obj->trans);
	obj->mtx = mtx_product(mtx_product(obj->i_trans, obj->mtx), mtx_trans(obj->i_trans));
}
