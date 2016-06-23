/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 18:12:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/22 16:29:56 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mtx		norm_vect(t_mtx mtx)
{
	t_mtx	out;
	double	length;

	out = mtx_init(4, 1);
	length = 1. / sqrt(mtx.mtx[0] * mtx.mtx[0] + mtx.mtx[1] * mtx.mtx[1] +
		mtx.mtx[2] * mtx.mtx[2]);
	set_vector(&out, mtx.mtx[0] * length, mtx.mtx[1] * length,
		mtx.mtx[2] * length);
	return (out);
}
