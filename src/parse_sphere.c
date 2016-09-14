/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:28:17 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/13 17:28:56 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_sphere_3(char **line, int *i, t_objenv objenv)
{
	t_material	*mat;
	t_sphere	*sphere;

	sphere = (t_sphere *)objenv.obj;
	if (!ft_strcmp(line[i[0]], "material"))
	{
		if (line[i[0] + 1] == NULL || !(ft_strlen(line[i[0] + 1]) > 0)
			|| !(mat = get_material(objenv.env, line[++i[0]])))
			return (return_print("Error parsing sphere material", 0));
		else
			objenv.obj->mat = mat;
	}
	else if (!ft_strcmp(line[i[0]], "start_height"))
	{
		if (!parse_double(line, i, &sphere->h1))
			return (return_print("Error parsing sphere start height", 0));
	}
	else if (!ft_strcmp(line[i[0]], "end_height"))
	{
		if (!parse_double(line, i, &sphere->h2))
			return (return_print("Error parsing sphere end height", 0));
	}
	return (1);
}

static int	parse_sphere_2(char **line, int *i, t_objenv objenv)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &objenv.tobj->trans))
			return (return_print("Error parsing sphere position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_mtx_rot(line, i, &objenv.tobj->rot))
			return (return_print("Error parsing sphere rotation", 0));
	}
	else if (!ft_strcmp(line[i[0]], "radius"))
	{
		if (!parse_double(line, i, &((t_sphere *)objenv.obj)->radius))
			return (return_print("Error parsing sphere radius", 0));
		else
		{
			if (((t_sphere *)objenv.obj)->radius < 0)
				return (return_print("Error, radius can't be negative", 0));
			((t_sphere *)objenv.obj)->radius = POW2(((t_sphere *)
				objenv.obj)->radius);
		}
	}
	return (parse_sphere_3(line, i, objenv));
}

static void	init_sphere(t_env *env, t_tobj *tobj, t_sphere *obj)
{
	tobj->rot = mtx_createscalemtx(1, 1, 1);
	tobj->scale = mtx_createscalemtx(1, 1, 1);
	obj->radius = 1;
	obj->h1 = 0;
	obj->h2 = 0;
	obj->mat = &env->base_material;
}

static void	last_setup(t_sphere *obj)
{
	double rad;

	rad = sqrt(obj->radius);
	set_vector(&obj->aabb[0], obj->trans.trans.mtx[3] - rad,
		obj->trans.trans.mtx[7] - rad,
		obj->trans.trans.mtx[11] - rad);
	set_vector(&obj->aabb[1], obj->trans.trans.mtx[3] + rad,
		obj->trans.trans.mtx[7] + rad,
		obj->trans.trans.mtx[11] + rad);
	if (obj->h1 == obj->h2)
	{
		obj->h1 = -rad;
		obj->h2 = rad;
	}
}

int			parse_sphere(t_env *env, char **line)
{
	int			i[2];
	t_tobj		tobj;
	t_sphere	*obj;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((obj = (t_sphere *)ft_memalloc(sizeof(t_obj))) == NULL ||
		(lst = ft_lstnewfrom(obj, sizeof(*obj))) == NULL)
		return (return_print("malloc error", 0));
	init_sphere(env, &tobj, obj);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_sphere_2(line, i, set_objenv(env, (t_obj *)obj, &tobj)) == 0)
			return (0);
	transform_object((t_obj *)obj, &tobj);
	obj->inter = sphere_inter;
	obj->normal = sphere_normal;
	last_setup(obj);
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 1 ? 1 : return_print("error sphere imcomplete", 0));
}
