/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:28:17 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/01 13:23:51 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	parse_sphere_4(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "shininess"))
	{
		if (!parse_double(line, i, &obj->shine))
			return (return_print("Error parsing sphere shininess", 0));
		else
			i[1] |= 64;
	}
	else if (!ft_strcmp(line[i[0]], "radius"))
	{
		if (!parse_double(line, i, &tobj->scale.mtx[0]))
			return (return_print("Error parsing sphere radius", 0));
		else
		{
			tobj->scale = mtx_createscalemtx(tobj->scale.mtx[0],
				tobj->scale.mtx[0], tobj->scale.mtx[0]);
			i[1] |= 2;
		}
	}
	return (1);
}

static int	parse_sphere_3(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "ambiant"))
	{
		if (!parse_double(line, i, &obj->k_ambiant))
			return (return_print("Error parsing sphere ambiant", 0));
		else
			i[1] |= 8;
	}
	else if (!ft_strcmp(line[i[0]], "specular"))
	{
		if (!parse_double(line, i, &obj->k_spec))
			return (return_print("Error parsing sphere specular", 0));
		else
			i[1] |= 16;
	}
	else if (!ft_strcmp(line[i[0]], "diffuse"))
	{
		if (!parse_double(line, i, &obj->k_diffuse))
			return (return_print("Error parsing sphere diffuse", 0));
		else
			i[1] |= 32;
	}
	return (parse_sphere_4(line, i, obj, tobj));
}

static int	parse_sphere_2(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &tobj->trans))
			return (return_print("Error parsing sphere position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "color"))
	{
		if (!parse_color(line, i, &obj->color))
			return (return_print("Error parsing sphere color", 0));
		else
			i[1] |= 4;
	}
	return (parse_sphere_3(line, i, obj, tobj));
}

int			parse_sphere(t_env *env, char **line)
{
	int			i[2];
	t_tobj		tobj;
	t_obj		*obj;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL ||
		(lst = ft_lstnewfrom(obj, sizeof(*obj))) == NULL)
		return (return_print("malloc error", 0));
	//obj->mtx = env->sphere_mtx;
	tobj.rot = mtx_createscalemtx(1, 1, 1);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_sphere_2(line, i, obj, &tobj) == 0)
			return (0);
	transform_object(obj, &tobj);
	obj->inter = sphere_inter;
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 127 ? 1 : return_print("error sphere imcomplete", 0));
}
