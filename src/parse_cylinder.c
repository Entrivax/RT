/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:28:51 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:55:01 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_cylinder_4(char **line, int *i, t_cylinder *obj, t_tobj *tobj)
{
	(void)tobj;
	if (!ft_strcmp(line[i[0]], "shininess"))
	{
		if (!parse_double(line, i, &obj->shine))
			return (return_print("Error parsing cylinder shininess", 0));
		else
			i[1] |= 64;
	}
	else if (!ft_strcmp(line[i[0]], "radius"))
	{
		if (!parse_double(line, i, &obj->radius))
			return (return_print("Error parsing cylinder radius", 0));
		else
		{
			if (obj->radius < 0)
				return (return_print("Error, radius can't be negative", 0));
			obj->radius = POW2(obj->radius);
			i[1] |= 128;
		}
	}
	else if (!ft_strcmp(line[i[0]], "reflexion"))
	{
		if (!parse_double(line, i, &obj->refle))
			return (return_print("Error parsion cylinder reflexion", 0));
	}
	return (1);
}

static int	parse_cylinder_3(char **line, int *i, t_cylinder *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "ambiant"))
	{
		if (!parse_double(line, i, &obj->k_ambiant))
			return (return_print("Error parsing cylinder ambiant", 0));
		else
			i[1] |= 8;
	}
	else if (!ft_strcmp(line[i[0]], "specular"))
	{
		if (!parse_double(line, i, &obj->k_spec))
			return (return_print("Error parsing cylinder specular", 0));
		else
			i[1] |= 16;
	}
	else if (!ft_strcmp(line[i[0]], "diffuse"))
	{
		if (!parse_double(line, i, &obj->k_diffuse))
			return (return_print("Error parsing cylinder diffuse", 0));
		else
			i[1] |= 32;
	}
	return (parse_cylinder_4(line, i, obj, tobj));
}

static int	parse_cylinder_2(char **line, int *i, t_cylinder *obj, t_tobj *tobj)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_mtx_trans(line, i, &tobj->trans))
			return (return_print("Error parsing cylinder position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "rotation"))
	{
		if (!parse_mtx_rot(line, i, &tobj->rot))
			return (return_print("Error parsing cylinder rotation", 0));
		else
			i[1] |= 2;
	}
	else if (!ft_strcmp(line[i[0]], "color"))
	{
		if (!parse_color(line, i, &obj->color))
			return (return_print("Error parsing cylinder color", 0));
		else
			i[1] |= 4;
	}
	return (parse_cylinder_3(line, i, obj, tobj));
}

int			parse_cylinder(t_env *env, char **line)
{
	int			i[2];
	t_tobj		tobj;
	t_cylinder	*obj;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((obj = (t_cylinder *)ft_memalloc(sizeof(t_obj))) == NULL ||
		(lst = ft_lstnewfrom(obj, sizeof(*obj))) == NULL)
		return (return_print("malloc error", 0));
	tobj.scale = mtx_createscalemtx(1, 1, 1);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_cylinder_2(line, i, obj, &tobj) == 0)
			return (0);
	transform_object((t_obj *)obj, &tobj);
	obj->inter = cylinder_inter;
	obj->normal = cylinder_normal;
	if (env->scene->objects == NULL)
		env->scene->objects = lst;
	else
		ft_lstadd(&(env->scene->objects), lst);
	return (i[1] == 255 ? 1 : return_print("error cylinder imcomplete", 0));
}
