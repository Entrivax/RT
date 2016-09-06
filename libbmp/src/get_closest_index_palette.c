/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_index_palette.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 14:52:23 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/24 15:25:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"

/*static int			i_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}*/

static int			pow2(int a)
{
	return (a * a);
}

unsigned char		get_closest_index_palette(t_palette *palette, t_rgb rgb)
{
	int				i;
	int				dist;
	int				tdist;
	unsigned char	closest;

	i = -1;
	dist = 0xFFFFFF;
	while (++i < palette->count)
	{
		tdist = pow2(rgb.r - palette->colors[i].r)
			+ pow2(rgb.g - palette->colors[i].g)
			+ pow2(rgb.b - palette->colors[i].b);
		if (tdist < dist)
		{
			dist = tdist;
			closest = i;
		}
	}
	return (closest);
}
