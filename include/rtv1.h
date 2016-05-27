/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:02:41 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/27 13:40:47 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>

# include "libft.h"
# include "libmtx.h"
# include "mlx.h"

typedef struct		s_inter
{
	double			t;
	t_mtx			pos;
}					t_inter;

typedef struct		s_ray
{
	t_mtx			dir;
	t_mtx			pos;
}					t_ray;

typedef struct		s_camera
{
	t_mtx			dir;
	t_mtx			pos;
	t_mtx			x_indent;
	t_mtx			y_indent;
	double			vp_width;
	double			vp_height;
	double			vp_dist;
	double			rotx;
	double			roty;
	double			rotz;
	double			width;
	double			height;
}					t_camera;

typedef struct		s_rgb
{
	float			r;
	float			g;
	float			b;
}					t_rgb;

typedef struct		s_scene
{
	t_list			*objects;
	t_list			*lights;
	t_camera		*camera;
	t_rgb			bgcolor;
	t_rgb			i_ambiant;
}					t_scene;

typedef struct		s_img
{
	void			*img;
	char			*img_writable;
	int				bytes_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			bg_img;
	t_scene			*scene;
	t_mtx			sphere_mtx;
	t_mtx			plane_mtx;
	t_mtx			cylinder_mtx;
	t_mtx			cone_mtx;
}					t_env;

void				program(int argc, char **argv);

t_env				*init_env(void);
void				init_img(void *mlx, t_img *img, int width, int height);

void				set_img_pixel(t_img *img, int x, int y, t_rgb color);
void				set_mlx_hooks(t_env *env);
int					expose_hook(t_env *env);
int					loop_hook(t_env *env);

t_mtx				norm_vect(t_mtx mtx);

#endif
