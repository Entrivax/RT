/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:02:41 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/01 16:50:48 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>

# include "libft.h"
# include "libmtx.h"
# include "mlx.h"

# define LIMIT_MIN 0.00001
# define POW2(x) (x*x)

typedef struct		s_rgb
{
	float			r;
	float			g;
	float			b;
}					t_rgb;

typedef struct		s_light
{
	t_rgb			color;
	t_mtx			pos;
}					t_light;

typedef struct		s_tobj
{
	t_mtx			rot;
	t_mtx			trans;
	t_mtx			scale;
}					t_tobj;

typedef struct		s_obj
{
	t_mtx			mtx;
	t_mtx			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
}					t_obj;

typedef struct		s_inter
{
	double			t;
	t_mtx			pos;
}					t_inter;

typedef struct		s_ray
{
	t_mtx			dir;
	t_mtx			pos;
	t_obj			*closest;
	double			t;
}					t_ray;

typedef struct		s_res
{
	int				width;
	int				height;
}					t_res;

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
	double			fov;
	t_res			res;
}					t_camera;

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
	t_res			res;
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

/*
** Program start method
*/

void				program(int argc, char **argv);

/*
** Initialization methods
*/

t_env				*init_env(void);
void				init_img(void *mlx, t_img *img, int width, int height);

/*
** MLX methods
*/

void				set_img_pixel(t_img *img, int x, int y, t_rgb color);
void				set_mlx_hooks(t_env *env);
int					expose_hook(t_env *env);
int					loop_hook(t_env *env);

/*
** Math method
*/

char				solve_quadratic(double *abc, double *t1, double *t2);

t_mtx				norm_vect(t_mtx mtx);

/*
** Parse file method
*/

int					*parse_file(t_env *env, int fd);

/*
** Parsing helper methods
*/

int					parse_resolution(char **line, int *i, t_res *res);
int					parse_vector3(char **line, int *i, t_mtx *v);
int					parse_color(char **line, int *i, t_rgb *rgb);
int					parse_double(char **line, int *i, double *a);

/*
** Object parsing methods
*/

int					parse_scene(t_env *env, char **line);
int					parse_camera(t_env *env, char **line);
int					parse_cone(t_env *env, char **line);
int					parse_cylinder(t_env *env, char **line);
int					parse_plane(t_env *env, char **line);
int					parse_sphere(t_env *env, char **line);

/*
** Utils methods
*/
int					return_print(char *str, int return_state);

#endif
