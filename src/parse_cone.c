/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:42:56 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/01 15:06:12 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	parse_cone_4(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "shininess"))
	{
		if (!parse_double(line, i, &obj->shine))
			return (return_print("Error parsing cone shininess", 0));
		else
			i[1] |= 64;
	}
	else if (!ft_strcmp(line[i[0]], "angle"))
	{
		if (!parse_double(line, i, &obj->mtx.mtx[0 + env->cone_mtx.cols * 0]))
			return (return_print("Error parsing cone opening angle", 0));
		else
		{
			obj->mtx.mtx[0 + env->cone_mtx.cols * 0] =
				tan(obj->mtx.mtx[0 + env->cone_mtx.cols * 0] * M_PI / 180.);
			obj->mtx.mtx[1 + env->cone_mtx.cols * 1] =
				obj->mtx.mtx[0 + env->cone_mtx.cols * 0];
			i[1] |= 128;
		}
	}
	return (1);
}

static int	parse_cone_3(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "ambiant"))
	{
		if (!parse_double(line, i, &obj->k_ambiant))
			return (return_print("Error parsing cone ambiant", 0));
		else
			i[1] |= 8;
	}
	else if (!ft_strcmp(line[i[0]], "specular"))
	{
		if (!parse_double(line, i, &obj->k_spec))
			return (return_print("Error parsing cone specular", 0));
		else
			i[1] |= 16;
	}
	else if (!ft_strcmp(line[i[0]], "diffuse"))
	{
		if (!parse_double(line, i, &obj->k_diffuse))
			return (return_print("Error parsing cone diffuse", 0));
		else
			i[1] |= 32;
	}
	return (parse_cone_4(line, i, obj, tobj));
}

static int	parse_cone_2(char **line, int *i, t_obj *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_vector3(line, i, tobj->trans))
			return (return_print("Error parsing cone position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_vector3(line, i, &tobj->rot))
			return (return_print("Error parsing cone rotation", 0));
		else
			i[1] |= 2;
	}
	else if (!ft_strcmp(line[i[0]], "color"))
	{
		if (!parse_color(line, i, &obj->color))
			return (return_print("Error parsing cone color", 0));
		else
			i[1] |= 4;
	}
	return (parse_cone_3(line, i, obj, tobj));
}

int			parse_cone(t_env *env, char **line)
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
	obj->mtx = env->cone_mtx;
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_cone_2(line, i, obj, &tobj) == 0)
			return (0);
	transform_object(obj, &tobj);
	if (env->scene->primitives == NULL)
		env->scene->primitives = lst;
	else
		ft_lstadd(&(env->scene->primitives), lst);
	return (i[1] == 255 ? 1 : return_print("error cone imcomplete", 0));
}
