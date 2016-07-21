/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_negate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 12:07:20 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/20 16:24:15 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmtx.h"

t_mtx		mtx_negate(t_mtx mtx)
{
	int		i;
	t_mtx	out;

	out = mtx_init(mtx.rows, mtx.cols);
	i = -1;
	while (++i < mtx.cols * mtx.rows)
		out.mtx[i] = -mtx.mtx[i];
	return (out);
}
