/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_dotproduct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:32:28 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/24 15:20:31 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx	mtx_dotproduct(t_mtx mtx1, t_mtx mtx2)
{
	t_mtx	prod;
	int		x;
	int		y;

	prod = mtx_init(mtx1.rows, mtx2.cols);
	x = -1;
	while (++x < prod.cols)
	{
		y = -1;
		while (++y < prod.rows)
			prod.mtx[x + y * prod.cols] = mtx_dot(mtx1, mtx2, x, y);
	}
	return (prod);
}
