/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 12:14:05 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/07 13:34:01 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx		mtx_mult(t_mtx mtx, double mult)
{
	int		i;
	t_mtx	out;

	out = mtx_init(mtx.rows, mtx.cols);
	i = -1;
	while (++i < mtx.cols * mtx.rows)
		out.mtx[i] = mtx.mtx[i] * mult;
	return (out);
}
