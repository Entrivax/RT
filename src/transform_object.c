/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 14:59:54 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	obj->trans = mtx_dotproduct(mtx_dotproduct(tobj->rot, tobj->scale),
		tobj->trans);
	obj->mtx = mtx_dotproduct(obj->trans, obj->mtx);
}
