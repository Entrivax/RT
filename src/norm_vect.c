/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 18:12:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/27 14:40:39 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mtx		norm_vect(t_mtx mtx)
{
	t_mtx	out;
	double	length;
	int		y;

	out = mtx_init(4, 1);
	length = 0;
	y = -1;
	while (++y < out.rows)
		length += mtx.mtx[y * mtx.cols];
	y = -1;
	while (++y < out.rows)
		out.mtx[y * out.cols] = mtx.mtx[y * mtx.cols] / length;
	return (out);
}
