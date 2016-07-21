/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 14:55:30 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/08 14:56:06 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx	mtx_product(t_mtx mtx1, t_mtx mtx2)
{
	t_mtx	mtx;
	int		a;
	int		b;
	int		i;
	double	tmp;

	mtx = mtx_init(mtx1.rows, mtx2.cols);
	if (mtx1.cols != mtx2.rows)
		return (mtx);
	a = -1;
	while (++a < mtx.cols)
	{
		b = -1;
		while (++b < mtx.rows)
		{
			tmp = 0;
			i = -1;
			while (++i < mtx1.cols)
				tmp += VOM(mtx1, i, b) * VOM(mtx2, a, i);
			VOM(mtx, a, b) = tmp;
		}
	}
	return (mtx);
}
