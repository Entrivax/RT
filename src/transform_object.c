/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/07 15:56:28 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	obj->trans = mtx_product(mtx_product(tobj->scale, tobj->trans),
		tobj->rot);
	obj->mtx = mtx_product(obj->trans, obj->mtx);
}
