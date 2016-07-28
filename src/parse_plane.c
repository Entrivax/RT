/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:01:04 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 14:44:36 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	parse_plane_4(char **line, int *i, t_plane *obj, t_tobj *tobj)
{
	(void)tobj;
	if (!ft_strcmp(line[i[0]], "shininess"))
	{
		if (!parse_double(line, i, &obj->shine))
			return (return_print("Error parsing plane shininess", 0));
		else
			i[1] |= 64;
	}
	else if (!ft_strcmp(line[i[0]], "reflexion"))
	{
		if (!parse_double(line, i, &obj->refle))
			return (return_print("Error parsion plane reflexion", 0));
	}
	return (1);
}

static int	parse_plane_3(char **line, int *i, t_plane *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "ambiant"))
	{
		if (!parse_double(line, i, &obj->k_ambiant))
			return (return_print("Error parsing plane ambiant", 0));
		else
			i[1] |= 8;
	}
	else if (!ft_strcmp(line[i[0]], "specular"))
	{
		if (!parse_double(line, i, &obj->k_spec))
			return (return_print("Error parsing plane specular", 0));
		else
			i[1] |= 16;
	}
	else if (!ft_strcmp(line[i[0]], "diffuse"))
	{
		if (!parse_double(line, i, &obj->k_diffuse))
			return (return_print("Error parsing plane diffuse", 0));
		else
			i[1] |= 32;
	}
	return (parse_plane_4(line, i, obj, tobj));
}

static int	parse_plane_2(char **line, int *i, t_plane *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &tobj->trans))
			return (return_print("Error parsing plane position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_mtx_rot(line, i, &tobj->rot))
			return (return_print("Error parsing plane rotation", 0));
		else
			i[1] |= 2;
	}
	else if (!ft_strcmp(line[i[0]], "color"))
	{
		if (!parse_color(line, i, &obj->color))
			return (return_print("Error parsing plane color", 0));
		else
			i[1] |= 4;
	}
	return (parse_plane_3(line, i, obj, tobj));
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
	tobj.scale = mtx_createscalemtx(1, 1, 1);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_plane_2(line, i, obj, &tobj) == 0)
			return (0);
	transform_object((t_obj *)obj, &tobj);
	obj->inter = plane_inter;
	obj->normal = plane_normal;
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 127 ? 1 : return_print("error plane imcomplete", 0));
}
