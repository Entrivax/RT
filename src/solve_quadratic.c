/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:58:12 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/13 17:08:21 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	swap_quad(double *t1, double *t2)
{
	double	tmp;

	if (*t1 < LIMIT_MIN || (*t2 > LIMIT_MIN && *t2 < *t1))
	{
		tmp = *t1;
		*t1 = *t2;
		*t2 = tmp;
	}
	return (((*t1 > LIMIT_MIN) ? 1 : 0) + ((*t2 > LIMIT_MIN) ? 1 : 0));
}

char		solve_quadratic(double *abc, double *t)
{
	double	d;

	if (abc[0] == 1)
		d = POW2(abc[1]) - 4. * abc[2];
	else
		d = POW2(abc[1]) - 4. * abc[0] * abc[2];
	if (d < 0)
		return (0);
	if (d == 0)
	{
		t[0] = -abc[1] / (2 * abc[0]);
		return (1);
	}
	d = sqrt(d);
	t[0] = (-abc[1] - d) / (2 * abc[0]);
	t[1] = (-abc[1] + d) / (2 * abc[0]);
	return (swap_quad(t, t + 1));
}
