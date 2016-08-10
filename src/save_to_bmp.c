/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 13:48:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/10 12:58:01 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	write_header(t_env *env)
{
	short	tmp;
	int		tmp2;
	long	tmp0;

	tmp = 0x4d42;
	tmp0 = 0;
	write(env->fd, &tmp, 2);
	tmp2 = env->bg_img.res.width * env->bg_img.res.height * 3 + 54;
	write(env->fd, &tmp2, 4);
	write(env->fd, &tmp0, 4);
	tmp2 = 0x36;
	write(env->fd, &tmp2, 4);
	tmp2 = 0x28;
	write(env->fd, &tmp2, 4);
	write(env->fd, &env->bg_img.res.width, 4);
	write(env->fd, &env->bg_img.res.height, 4);
	tmp2 = 1 | (24 << 16);
	write(env->fd, &tmp2, 4);
	write(env->fd, &tmp0, 4);
	tmp2 = env->bg_img.res.width * env->bg_img.res.height * 3;
	write(env->fd, &tmp2, 4);
	tmp2 = 1;
	write(env->fd, &tmp2, 4);
	write(env->fd, &tmp2, 4);
	write(env->fd, &tmp0, 8);
}

static char	*prepare_buffer(char *pixels, size_t length)
{
	char	*buf;
	ssize_t	i;
	ssize_t	i2;

	if (!(buf = ft_memalloc(length / 4 * 3)))
		return (NULL);
	i = length;
	i2 = 0;
	while ((i -= 4) >= 0)
	{
		buf[i2] = pixels[i];
		buf[i2 + 1] = pixels[i + 1];
		buf[i2 + 2] = pixels[i + 2];
		i2 += 3;
	}
	return (buf);
}

void		save_to_bmp(t_env *env)
{
	char	*pixels;
	char	*buf;
	int		pitch;
	int		i;

	if (env->fd <= 0)
		return ;
	env->new_title = "rt @42 - Saving...";
	add_to_queue(env, update_title);
	pitch = env->bg_img.res.width * 4;
	write_header(env);
	if (!(pixels = malloc(sizeof(char) * (pitch * env->bg_img.res.height + 1))))
	{
		ft_putendl("malloc error");
		return ;
	}
	SDL_RenderReadPixels(env->bg_img.renderer, NULL, 0, pixels, pitch);
	i = env->bg_img.res.width * env->bg_img.res.height * 4;
	buf = prepare_buffer(pixels, i);
	write(env->fd, buf, i / 4 * 3);
	close(env->fd);
	free(pixels);
	env->fd = 0;
	env->new_title = "rt @42 - Saved!";
	add_to_queue(env, update_title);
}
