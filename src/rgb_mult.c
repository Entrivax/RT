/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:48:35 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:56:54 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rgb_mult(t_rgb *color, double mult)
{
	color->r *= mult;
	color->g *= mult;
	color->b *= mult;
}

t_rgb		rgb_mult_cpy(t_rgb color, double mult)
{
	t_rgb	ret;

	ret.r = color.r * mult;
	ret.g = color.g * mult;
	ret.b = color.b * mult;
	return (ret);
}
