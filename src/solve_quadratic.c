/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:58:12 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/01 16:06:28 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	solve_quadratic(double *abc, double *t1, double *t2)
{
	double d;

	if (abc[0] == 1)
		d = POW2(abc[1]) - 4. * abc[2];
	else
		d = POW2(abc[1]) - 4. * abc[0] * abc[2];
	if (d < 0)
		return (0);
	if (d == 0)
	{
		*t1 = -abc[1] / (2 * abc[0]);
		return (1);
	}
	d = sqrt(d);
	*t1 = (-abc[1] - d) / (2 * abc[0]);
	*t2 = (-abc[1] + d) / (2 * abc[0]);
	return (2);
}
