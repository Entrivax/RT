/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:11:34 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 16:32:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init_img(void *mlx, t_img *img, int width, int height)
{
	if ((img->img = mlx_new_image(mlx, width, height)) == NULL)
		return (return_print("error during image initialization", -1));
	img->img_writable = mlx_get_data_addr(img->img, &img->bytes_per_pixel,
		&img->size_line, &img->endian);
	img->bytes_per_pixel /= 8;
	img->res.width = width;
	img->res.height = height;
	return (0);
}
