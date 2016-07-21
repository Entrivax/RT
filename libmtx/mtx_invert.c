/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_invert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:32:43 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/13 17:05:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

static double	get_determinant(t_mtx *x)
{
	double	det;

	det = VOM(*x, 0, 0) * DET(VOM(*x, 1, 1), VOM(*x, 1, 2), VOM(*x, 1, 3),
								VOM(*x, 2, 1), VOM(*x, 2, 2), VOM(*x, 2, 3),
								VOM(*x, 3, 1), VOM(*x, 3, 2), VOM(*x, 3, 3));
	det -= VOM(*x, 0, 1) * DET(VOM(*x, 1, 0), VOM(*x, 1, 2), VOM(*x, 1, 3),
								VOM(*x, 2, 0), VOM(*x, 2, 2), VOM(*x, 2, 3),
								VOM(*x, 3, 0), VOM(*x, 3, 2), VOM(*x, 3, 3));
	det += VOM(*x, 0, 2) * DET(VOM(*x, 1, 0), VOM(*x, 1, 1), VOM(*x, 1, 3),
								VOM(*x, 2, 0), VOM(*x, 2, 1), VOM(*x, 2, 3),
								VOM(*x, 3, 0), VOM(*x, 3, 1), VOM(*x, 3, 3));
	det -= VOM(*x, 0, 3) * DET(VOM(*x, 1, 0), VOM(*x, 1, 1), VOM(*x, 1, 2),
								VOM(*x, 2, 0), VOM(*x, 2, 1), VOM(*x, 2, 2),
								VOM(*x, 3, 0), VOM(*x, 3, 1), VOM(*x, 3, 2));
	return (det);
}

static void		fill_invert2(t_mtx *o, t_mtx *x, double det)
{
	VOM(*x, 2, 0) = DET(VOM(*o, 1, 0), VOM(*o, 1, 1), VOM(*o, 1, 3),
						VOM(*o, 2, 0), VOM(*o, 2, 1), VOM(*o, 2, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 3)) / det;
	VOM(*x, 2, 1) = -DET(VOM(*o, 0, 0), VOM(*o, 0, 1), VOM(*o, 0, 3),
						VOM(*o, 2, 0), VOM(*o, 2, 1), VOM(*o, 2, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 3)) / det;
	VOM(*x, 2, 2) = DET(VOM(*o, 0, 0), VOM(*o, 0, 1), VOM(*o, 0, 3),
						VOM(*o, 1, 0), VOM(*o, 1, 1), VOM(*o, 1, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 3)) / det;
	VOM(*x, 2, 3) = -DET(VOM(*o, 0, 1), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 1, 1), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 2, 1), VOM(*o, 2, 2), VOM(*o, 2, 3)) / det;
	VOM(*x, 3, 0) = -DET(VOM(*o, 1, 0), VOM(*o, 1, 1), VOM(*o, 1, 2),
						VOM(*o, 2, 0), VOM(*o, 2, 1), VOM(*o, 2, 2),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 2)) / det;
	VOM(*x, 3, 1) = DET(VOM(*o, 0, 0), VOM(*o, 0, 1), VOM(*o, 0, 2),
						VOM(*o, 2, 0), VOM(*o, 2, 1), VOM(*o, 2, 2),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 2)) / det;
	VOM(*x, 3, 2) = -DET(VOM(*o, 0, 0), VOM(*o, 0, 1), VOM(*o, 0, 2),
						VOM(*o, 1, 0), VOM(*o, 1, 1), VOM(*o, 1, 2),
						VOM(*o, 3, 0), VOM(*o, 3, 1), VOM(*o, 3, 2)) / det;
	VOM(*x, 3, 3) = DET(VOM(*o, 0, 0), VOM(*o, 0, 1), VOM(*o, 0, 2),
						VOM(*o, 1, 0), VOM(*o, 1, 1), VOM(*o, 1, 2),
						VOM(*o, 2, 0), VOM(*o, 2, 1), VOM(*o, 2, 2)) / det;
}

static void		fill_invert(t_mtx *o, t_mtx *x, double det)
{
	VOM(*x, 0, 0) = DET(VOM(*o, 1, 1), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 2, 1), VOM(*o, 2, 2), VOM(*o, 2, 3),
						VOM(*o, 3, 1), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 0, 1) = -DET(VOM(*o, 0, 1), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 2, 1), VOM(*o, 2, 2), VOM(*o, 2, 3),
						VOM(*o, 3, 1), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 0, 2) = DET(VOM(*o, 0, 1), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 1, 1), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 3, 1), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 0, 3) = -DET(VOM(*o, 0, 1), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 1, 1), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 2, 1), VOM(*o, 2, 2), VOM(*o, 2, 3)) / det;
	VOM(*x, 1, 0) = -DET(VOM(*o, 1, 0), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 2, 0), VOM(*o, 2, 2), VOM(*o, 2, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 1, 1) = DET(VOM(*o, 0, 0), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 2, 0), VOM(*o, 2, 2), VOM(*o, 2, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 1, 2) = -DET(VOM(*o, 0, 0), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 1, 0), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 3, 0), VOM(*o, 3, 2), VOM(*o, 3, 3)) / det;
	VOM(*x, 1, 3) = DET(VOM(*o, 0, 0), VOM(*o, 0, 2), VOM(*o, 0, 3),
						VOM(*o, 1, 0), VOM(*o, 1, 2), VOM(*o, 1, 3),
						VOM(*o, 2, 0), VOM(*o, 2, 2), VOM(*o, 2, 3)) / det;
	fill_invert2(o, x, det);
}

t_mtx			mtx_invert(t_mtx mtx)
{
	t_mtx	x;
	double	det;

	if (mtx.rows != mtx.cols && mtx.rows != 4)
		return (mtx);
	x = mtx_init(4, 4);
	det = get_determinant(&mtx);
	if (det == 0)
		return (x);
	fill_invert(&mtx, &x, det);
	return (x);
}
