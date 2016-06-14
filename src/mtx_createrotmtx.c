/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_createrotmtx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 12:12:12 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/14 14:41:18 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_cosine(double *cosin, double rotx, double roty, double rotz)
{
	cosin[0] = cos(rotx);
	cosin[1] = sin(rotx);
	cosin[2] = cos(roty);
	cosin[3] = sin(roty);
	cosin[4] = cos(rotz);
	cosin[5] = sin(rotz);
}

t_mtx			mtx_createrotmtx(double rotx, double roty, double rotz)
{
	double	cosin[6];
	t_mtx	mtx;

	set_cosine(cosin, rotx, roty, rotz);
	mtx = mtx_init(4, 4);
	mtx.mtx[0] = cosin[2] * cosin[4];
	mtx.mtx[1] = -cosin[2] * cosin[5];
	mtx.mtx[2] = cosin[3];
	mtx.mtx[4] = cosin[1] * cosin[3] * cosin[4] + cosin[0] * cosin[5];
	mtx.mtx[5] = -cosin[1] * cosin[3] * cosin[5] + cosin[0] * cosin[4];
	mtx.mtx[6] = -cosin[1] * cosin[2];
	mtx.mtx[8] = -cosin[0] * cosin[3] * cosin[4] + cosin[1] * cosin[5];
	mtx.mtx[9] = cosin[0] * cosin[3] * cosin[5] + cosin[1] * cosin[4];
	mtx.mtx[10] = cosin[0] * cosin[2];
	mtx.mtx[15] = 1;
	return (mtx);
}

t_mtx			mtx_applyrot(t_mtx *mtx, double rotx, double roty, double rotz)
{
	t_mtx	rot;

	rot = mtx_createrotmtx(rotx, roty, rotz);
	return (mtx_dotproduct(rot, *mtx));
}
