/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:22:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/11 12:44:09 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <stdio.h>
void	print_mtx(t_mtx *mtx)
{
	int x;
	int y;

	printf("Size: %d;%d\n", mtx->cols, mtx->rows);
	y = -1;
	while (++y < mtx->rows)
	{
		printf("[");
		x = -1;
		while (++x < mtx->cols)
			printf("%lf\t", VOM(*mtx, x, y));
		printf("]\n");
	}
}

void	transform_object(t_obj *obj, t_tobj *tobj)
{
	/*obj->trans = mtx_product(mtx_product(tobj->scale, tobj->trans),
		tobj->rot);*/
	tobj->ftrans = mtx_product(tobj->trans, mtx_product(tobj->rot,
		tobj->scale));
	//tobj->rotxscale = mtx_product(tobj->rot, tobj->scale);
	//tobj->i_rotxscale = mtx_invert(tobj->rotxscale);
	tobj->i_trans = mtx_invert(tobj->trans);
	tobj->i_rot = mtx_invert(tobj->rot);
	tobj->i_scale = mtx_invert(tobj->scale);
	tobj->i_ftrans = mtx_product(tobj->i_scale, mtx_product(tobj->i_trans,
		tobj->i_rot));
	obj->trans = *tobj;
	//obj->mtx = mtx_product(mtx_product(obj->i_trans, obj->mtx), mtx_trans(obj->i_trans));
}
