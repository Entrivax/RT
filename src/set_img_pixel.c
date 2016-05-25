/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:01:21 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/25 18:20:09 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	color_to_int(t_rgb *color)
{
	int		intcolor;

	if (color->r < 0)
		color->r = 0;
	else if (color->r > 1)
		color->r = 1;
	if (color->g < 0)
		color->g = 0;
	else if (color->g > 1)
		color->g = 1;
	if (color->b < 0)
		color->b = 0;
	else if (color->b > 1)
		color->b = 1;
	intcolor = (int)(color->b * 255) & 0xff;
	intcolor += ((int)(color->g * 255) << 8) & 0xff00;
	intcolor += ((int)(color->r * 255) << 16) & 0xff0000;
	return (intcolor);
}

void		set_img_pixel(t_img *img, int x, int y, t_rgb color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		(*(unsigned int *)(img->img_writable + x * img->bytes_per_pixel +
			y * img->size_line)) = mlx_get_color_value(env->mlx,
			color_to_int(&color));
	}
}
