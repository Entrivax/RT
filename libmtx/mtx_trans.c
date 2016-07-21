/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 13:57:09 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/08 12:32:18 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx	mtx_trans(t_mtx mtx)
{
	t_mtx	mtx2;
	int		x;
	int		y;

	mtx2 = mtx_init(mtx.cols, mtx.rows);
	x = -1;
	while (++x < mtx.rows)
	{
		y = -1;
		while (++y < mtx.cols)
			mtx2.mtx[x + y * mtx2.cols] = mtx.mtx[x * mtx.cols + y];
	}
	return (mtx2);
}
