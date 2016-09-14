/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:01:04 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/12 15:54:27 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_plane_2(char **line, int *i, t_objenv objenv)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &objenv.tobj->trans))
			return (return_print("Error parsing plane position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_mtx_rot(line, i, &objenv.tobj->rot))
			return (return_print("Error parsing plane rotation", 0));
	}
	else if (!ft_strcmp(line[i[0]], "material"))
	{
		if (line[i[0] + 1] == NULL || !(ft_strlen(line[i[0] + 1]) > 0))
			return (return_print("Error parsing plane material", 0));
		else
			objenv.obj->mat = get_material(objenv.env, line[++i[0]]);
	}
	return (1);
}

static void	init_plane(t_env *env, t_tobj *tobj, t_plane *obj)
{
	tobj->rot = mtx_createscalemtx(1, 1, 1);
	tobj->scale = mtx_createscalemtx(1, 1, 1);
	obj->mat = &env->base_material;
	set_vector(&obj->aabb[0], -1.0 / 0.0, -1.0 / 0.0, -1.0 / 0.0);
	set_vector(&obj->aabb[1], 1.0 / 0.0, 1.0 / 0.0, 1.0 / 0.0);
}

int			parse_plane(t_env *env, char **line)
{
	int			i[2];
	t_tobj		tobj;
	t_plane		*obj;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((obj = (t_plane *)ft_memalloc(sizeof(t_obj))) == NULL ||
		(lst = ft_lstnewfrom(obj, sizeof(*obj))) == NULL)
		return (return_print("malloc error", 0));
	init_plane(env, &tobj, obj);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_plane_2(line, i, set_objenv(env, (t_obj *)obj, &tobj)) == 0)
			return (0);
	transform_object((t_obj *)obj, &tobj);
	obj->inter = plane_inter;
	obj->normal = plane_normal;
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 1 ? 1 : return_print("error plane imcomplete", 0));
}
