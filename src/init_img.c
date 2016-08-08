/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:11:34 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:50:54 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_img(t_env *env, t_img *img, int width, int height)
{
	if ((img->img = SDL_CreateTexture(env->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, width, height)) == NULL)
		return (return_print("error during image initialization", -1));
	pthread_mutex_init(&img->mutex, NULL);
	img->renderer = env->renderer;
	SDL_QueryTexture(img->img, NULL, NULL, &img->res.width, &img->res.height);
	return (0);
}
