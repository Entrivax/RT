/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 12:00:40 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/07 13:53:26 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx		mtx_add(t_mtx mtx1, t_mtx mtx2)
{
	int		x;
	int		y;
	t_mtx	out;

	out = mtx_init(mtx1.rows, mtx1.cols);
	if (mtx1.cols != mtx2.cols || mtx1.rows != mtx2.rows)
		return (out);
	x = -1;
	while (++x < mtx1.cols)
	{
		y = -1;
		while (++y < mtx1.rows)
			out.mtx[x + y * out.cols] = mtx1.mtx[x + y * out.cols]
				+ mtx2.mtx[x + y * out.cols];
	}
	return (out);
}
