/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:02:41 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/13 17:27:20 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# include "keycodes.h"
# include "libft.h"
# include "libmtx.h"
# include "libbmp.h"
# include "SDL.h"

# define LIMIT_MIN 0.00001
# define POW2(x) (x*x)
# define DOTV(a, b) (a.mtx[0]*b.mtx[0] + a.mtx[1]*b.mtx[1] + a.mtx[2]*b.mtx[2])
# define NEAR(a, b) (a - LIMIT_MIN < b && b < a + LIMIT_MIN)
# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)

typedef struct s_ray	t_ray;
typedef struct s_obj	t_obj;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct		s_light
{
	t_color			color;
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

typedef struct		s_material
{
	char			*name;
	double			shine;
	double			k_ambiant;
	double			k_spec;
	double			k_diffuse;
	double			refle;
	double			opacity;
	t_color			color;
}					t_material;

struct				s_obj
{
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_mtx			aabb[2];
	t_tobj			trans;
	t_material		*mat;
};

typedef struct		s_sphere
{
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_mtx			aabb[2];
	t_tobj			trans;
	t_material		*mat;
	double			radius;
	double			h1;
	double			h2;
}					t_sphere;

typedef struct		s_cylinder
{
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_mtx			aabb[2];
	t_tobj			trans;
	t_material		*mat;
	double			radius;
	double			h;
}					t_cylinder;

typedef struct		s_cone
{
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_mtx			aabb[2];
	t_tobj			trans;
	t_material		*mat;
	double			angle;
	double			h1;
	double			h2;
}					t_cone;

typedef struct		s_plane
{
	double			(*inter)(t_obj *, t_ray);
	t_mtx			(*normal)(t_obj *, t_inter *, t_ray *);
	t_mtx			aabb[2];
	t_tobj			trans;
	t_material		*mat;
}					t_plane;

struct				s_ray
{
	t_mtx			dir;
	t_mtx			invdir;
	t_mtx			pos;
	t_obj			*closest;
	double			t;
	double			pene;
};

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
	t_list			*materials;
	t_camera		*camera;
	t_color			bgcolor;
	t_color			i_ambiant;
	double			ambbaseimpact;
	double			ambcoefimpact;
	int				max_ref;
}					t_scene;

typedef struct		s_img
{
	SDL_Texture		*img;
	SDL_Renderer	*renderer;
	pthread_mutex_t	mutex;
	t_res			res;
}					t_img;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	t_img			bg_img;
	char			loop;
	int				n_threads;
	int				real_n_threads;
	char			print_time;
	char			*new_title;
	unsigned int	processed_pixels;
	struct timeval	clocks[2];
	pthread_t		*threads;
	pthread_t		clockthread;
	pthread_mutex_t	mutex;
	t_scene			*scene;
	t_material		base_material;
	t_mtx			sphere_mtx;
	t_mtx			plane_mtx;
	t_mtx			cylinder_mtx;
	t_mtx			cone_mtx;
	char			*outputname;
	t_list			*queue;
	pthread_mutex_t	queuemutex;
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
	t_color			*color;
	t_color			*specular;
	t_color			*diffuse;
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
int					init_img(t_env *env, t_img *img, int width, int height);
int					init_camera(t_camera *camera);
void				init_material(t_material *mat);

/*
** Destruction method
*/

void				destruct_env(t_env *env);

/*
** SDL methods
*/

void				sdl_loop(t_env *env);
void				set_img_pixel(t_img *img, int x, int y, t_color color);
void				update_title(t_env *env);
void				set_mlx_hooks(t_env *env);
int					expose_hook(t_env *env);
int					loop_hook(t_env *env);
int					key_hook(int keycode, t_env *env);
int					mouse_hook(int button, int x, int y, t_env *env);

/*
** Color methods
*/

t_color				rgb_new(float r, float g, float b);
void				rgb_clamp(t_color *color);
void				rgb_add(t_color *color, float r, float g, float b);
void				rgb_add_rgb(t_color *colora, t_color colorb);
void				rgb_div(t_color *color, double n);
void				rgb_mult(t_color *color, double mult);
t_color				rgb_mult_cpy(t_color color, double mult);

/*
** Math method
*/

char				solve_quadratic(double *abc, double *t);
void				set_vector(t_mtx *mtx, double x, double y, double z);
double				dot_vect(t_mtx *vect1, t_mtx *vect2);
t_mtx				norm_vect(t_mtx mtx);
t_mtx				mtx_createrotmtx(double rotx, double roty, double rotz);
t_mtx				mtx_applyrot(t_mtx *mtx, double rotx, double roty,
											double rotz);
t_mtx				mtx_createscalemtx(double scalex, double scaley,
											double scalez);
void				transform_object(t_obj *obj, t_tobj *tobj);
t_mtx				vect_reflect(t_mtx i, t_mtx n);

/*
** Parse file method
*/

int					parse_file(t_env *env, char *file);

/*
** Parsing helper methods
*/

int					parse_resolution(char **line, int *i, t_res *res);
int					parse_vector3(char **line, int *i, t_mtx *v);
int					parse_color(char **line, int *i, t_color *rgb);
int					parse_double(char **line, int *i, double *a);
int					parse_int(char **line, int *i, int *a);
int					parse_mtx_trans(char **line, int *i, t_mtx *v);
int					parse_mtx_rot(char **line, int *i, t_mtx *v);

/*
** Object parsing methods
*/

int					parse_args(t_env *env, int argc, char **argv);
int					parse_scene(t_env *env, char **line);
int					parse_camera(t_env *env, char **line);
int					parse_cone(t_env *env, char **line);
int					parse_cylinder(t_env *env, char **line);
int					parse_plane(t_env *env, char **line);
int					parse_sphere(t_env *env, char **line);
int					parse_light(t_env *env, char **line);
int					parse_material(t_env *env, char **line);

/*
** RT methods
*/
void				*render_scene(void *arg);
t_color				compute_color(t_env *env, t_ray *ray, int ref,
									float refrem);
double				find_dist(t_ray ray, t_obj *obj);
char				find_closest(t_scene *scene, t_ray *ray);
t_mtx				get_normal(t_ray ray);
t_color				compute_light(t_scene *scene, t_ray *ray);
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
char				aabb(t_ray *ray, t_obj *obj);

/*
** Utils methods
*/
void				add_to_queue(t_env *env, void (*method)(t_env *env));
void				print_usage(char *binary_name);
int					return_print(char *str, int return_state);
void				save_to_bmp(t_env *env);
void				print_memory(const void *addr, size_t size);
t_objenv			set_objenv(t_env *env, t_obj *obj, t_tobj *tobj);
t_material			*get_material(t_env *env, const char *id);

#endif
