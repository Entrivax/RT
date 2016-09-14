/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:42:56 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/13 17:34:51 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_cone_3(char **line, int *i, t_objenv *objenv)
{
	double		a;
	t_cone		*cone;

	cone = (t_cone *)objenv->obj;
	if (!ft_strcmp(line[i[0]], "angle"))
	{
		if (!parse_double(line, i, &a))
			return (return_print("Error parsing cone opening angle", 0));
		else
		{
			if (a < 0)
				return (return_print("Error, cone angle can't be negative", 0));
			((t_cone *)objenv->obj)->angle = tan(a * M_PI / 180.);
			i[1] |= 4;
		}
	}
	else if (!ft_strcmp(line[i[0]], "start_height"))
	{
		if (!parse_double(line, i, &cone->h1))
			return (return_print("Error parsing cone start height", 0));
	}
	else if (!ft_strcmp(line[i[0]], "end_height"))
	{
		if (!parse_double(line, i, &cone->h2))
			return (return_print("Error parsing cone end height", 0));
	}
	return (1);
}

static int	parse_cone_2(char **line, int *i, t_objenv objenv)
{
	t_material	*mat;

	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &objenv.tobj->trans))
			return (return_print("Error parsing cone position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_mtx_rot(line, i, &objenv.tobj->rot))
			return (return_print("Error parsing cone rotation", 0));
	}
	else if (!ft_strcmp(line[i[0]], "material"))
	{
		if (line[i[0] + 1] == NULL || !(ft_strlen(line[i[0] + 1]) > 0)
			|| !(mat = get_material(objenv.env, line[++i[0]])))
			return (return_print("Error parsing cone material", 0));
		else
			objenv.obj->mat = mat;
	}
	return (parse_cone_3(line, i, &objenv));
}

static void	init_cone(t_env *env, t_tobj *tobj, t_cone *obj)
{
	tobj->rot = mtx_createscalemtx(1, 1, 1);
	tobj->scale = mtx_createscalemtx(1, 1, 1);
	obj->angle = 90 * M_PI / 180.;
	obj->mat = &env->base_material;
	obj->h1 = -1;
	obj->h2 = 1;
	set_vector(&obj->aabb[0], -1.0 / 0.0, -1.0 / 0.0, -1.0 / 0.0);
	set_vector(&obj->aabb[1], 1.0 / 0.0, 1.0 / 0.0, 1.0 / 0.0);
}

static void	check(t_cone *obj)
{
	double		tmp;

	if (obj->h1 > obj->h2)
	{
		tmp = obj->h2;
		obj->h2 = obj->h1;
		obj->h1 = tmp;
	}
}

int			parse_cone(t_env *env, char **line)
{
	int			i[2];
	t_tobj		tobj;
	t_cone		*obj;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((obj = (t_cone *)ft_memalloc(sizeof(t_cone))) == NULL ||
		(lst = ft_lstnewfrom(obj, sizeof(*obj))) == NULL)
		return (return_print("malloc error", 0));
	init_cone(env, &tobj, obj);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_cone_2(line, i, set_objenv(env, (t_obj *)obj, &tobj)) == 0)
			return (0);
	transform_object((t_obj *)obj, &tobj);
	obj->inter = cone_inter;
	obj->normal = cone_normal;
	check(obj);
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 5 ? 1 : return_print("error cone imcomplete", 0));
}
