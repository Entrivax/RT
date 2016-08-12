/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:28:17 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/12 14:36:21 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_sphere_3(char **line, int *i, t_objenv objenv)
{
	t_material	*mat;

	if (!ft_strcmp(line[i[0]], "material"))
	{
		if (line[i[0] + 1] == NULL || !(ft_strlen(line[i[0] + 1]) > 0)
			|| !(mat = get_material(objenv.env, line[++i[0]])))
			return (return_print("Error parsing sphere material", 0));
		else
			objenv.obj->mat = mat;
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
	obj->mat = &env->base_material;
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
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 1 ? 1 : return_print("error sphere imcomplete", 0));
}
