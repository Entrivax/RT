/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:41:55 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/24 15:36:18 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

double	mtx_dot(t_mtx mtx1, t_mtx mtx2, int a, int b)
{
	double	prod;
	int		i;

	prod = 0;
	i = -1;
	while (++i < mtx1.cols)
		prod += mtx1.mtx[a * mtx1.cols + i] * mtx2.mtx[i * mtx2.cols + b];
	return (prod);
}
