/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:02:41 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 12:37:40 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include "keycodes.h"
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
	double			power;
}					t_light;

typedef struct		s_tobj
{
	t_mtx			rot;
	t_mtx			trans;
	t_mtx			scale;
	t_mtx			ftrans;
	t_mtx			i_rot;
	t_mtx			i_trans;
	t_mtx			i_scale;
	t_mtx			i_ftrans;
}					t_tobj;

typedef struct		s_inter
{
	double			t;
	t_mtx			pos;
}					t_inter;

typedef struct s_ray	t_ray;
typedef struct s_obj	t_obj;
struct				s_obj
{
	int				type;
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_tobj			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
};

typedef struct		s_sphere
{
	int				type;
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_tobj			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
	double			radius;
}					t_sphere;

typedef struct		s_cylinder
{
	int				type;
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_tobj			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
	double			radius;
}					t_cylinder;

typedef struct		s_cone
{
	int				type;
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_tobj			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
	double			angle;
}					t_cone;

typedef struct		s_plane
{
	int				type;
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_tobj			trans;
	t_rgb			color;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
}					t_plane;

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
	t_mtx			vp_up_left;
	double			vp_width;
	double			vp_height;
	double			vp_dist;
	double			rotx;
	double			roty;
	double			rotz;
	double			fov;
	int				antialiasing;
	t_res			res;
}					t_camera;

typedef struct		s_scene
{
	t_list			*objects;
	t_list			*lights;
	t_camera		*camera;
	t_rgb			bgcolor;
	t_rgb			i_ambiant;
	double			ambbaseimpact;
	double			ambcoefimpact;
}					t_scene;

typedef struct		s_img
{
	void			*img;
	char			*img_writable;
	int				bytes_per_pixel;
	int				size_line;
	int				endian;
	t_res			res;
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

typedef struct		s_objenv
{
	t_env			*env;
	t_tobj			*tobj;
	t_obj			*obj;
}					t_objenv;

typedef struct		s_phpa
{
	t_ray			*lray;
	t_ray			*ray;
	t_rgb			*color;
	t_rgb			*specular;
	t_rgb			*diffuse;
	t_light			*light;
	t_camera		*camera;
	t_mtx			normal;
}					t_phpa;

/*
** Program start method
*/

void				program(int argc, char **argv);

/*
** Initialization methods
*/

t_env				*init_env(void);
int					init_win(t_env *env);
int					init_img(void *mlx, t_img *img, int width, int height);
int					init_camera(t_camera *camera);

/*
** MLX methods
*/

void				set_img_pixel(t_img *img, int x, int y, t_rgb color);
void				set_mlx_hooks(t_env *env);
int					expose_hook(t_env *env);
int					loop_hook(t_env *env);
int					key_hook(int keycode, t_env *env);
int					mouse_hook(int button, int x, int y, t_env *env);

/*
** Color methods
*/

t_rgb				rgb_new(float r, float g, float b);
void				rgb_clamp(t_rgb *color);
void				rgb_add(t_rgb *color, float r, float g, float b);
void				rgb_add_rgb(t_rgb *colora, t_rgb colorb);
void				rgb_div(t_rgb *color, double n);

/*
** Math method
*/

char				solve_quadratic(double *abc, double *t1, double *t2);

void				set_vector(t_mtx *mtx, double x, double y, double z);
double				dot_vect(t_mtx *vect1, t_mtx *vect2);
t_mtx				norm_vect(t_mtx mtx);
t_mtx				mtx_createrotmtx(double rotx, double roty, double rotz);
t_mtx				mtx_applyrot(t_mtx *mtx, double rotx, double roty, double rotz);
t_mtx				mtx_createscalemtx(double scalex, double scaley, double scalez);
void				transform_object(t_obj *obj, t_tobj *tobj);

/*
** Parse file method
*/

int					parse_file(t_env *env, char *file);

/*
** Parsing helper methods
*/

int					parse_resolution(char **line, int *i, t_res *res);
int					parse_vector3(char **line, int *i, t_mtx *v);
int					parse_color(char **line, int *i, t_rgb *rgb);
int					parse_double(char **line, int *i, double *a);
int					parse_int(char **line, int *i, int *a);
int					parse_mtx_trans(char **line, int *i, t_mtx *v);
int					parse_mtx_rot(char **line, int *i, t_mtx *v);

/*
** Object parsing methods
*/

int					parse_scene(t_env *env, char **line);
int					parse_camera(t_env *env, char **line);
int					parse_cone(t_env *env, char **line);
int					parse_cylinder(t_env *env, char **line);
int					parse_plane(t_env *env, char **line);
int					parse_sphere(t_env *env, char **line);
int					parse_light(t_env *env, char **line);

/*
** RT methods
*/
void				render_scene(t_env *env);
double				find_dist(t_ray ray, t_obj *obj);
char				find_closest(t_scene *scene, t_ray *ray);
t_mtx				get_normal(t_ray ray);
t_rgb				compute_light(t_scene *scene, t_ray *ray);
t_ray				invert_ray(t_ray ray);
void				phong(t_phpa *ph);
double				sphere_inter(t_obj *obj, t_ray ray);
t_mtx				sphere_normal(t_obj *obj, t_inter *inter, t_ray *ray);
double				cylinder_inter(t_obj *obj, t_ray ray);
t_mtx				cylinder_normal(t_obj *obj, t_inter *inter, t_ray *ray);
double				cone_inter(t_obj *obj, t_ray ray);
t_mtx				cone_normal(t_obj *obj, t_inter *inter, t_ray *ray);
double				plane_inter(t_obj *obj, t_ray ray);
t_mtx				plane_normal(t_obj *obj, t_inter *inter, t_ray *ray);

/*
** Utils methods
*/
int					return_print(char *str, int return_state);
t_objenv			set_objenv(t_env *env, t_obj *obj, t_tobj *tobj);

#endif
