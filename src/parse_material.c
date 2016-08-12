/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 14:15:07 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/12 14:26:53 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_material(t_material *mat)
{
	mat->color = rgb_new(1, 1, 1);
	mat->shine = 1;
	mat->k_ambiant = 1;
	mat->k_spec = 1;
	mat->k_diffuse = 1;
	mat->refle = 0;
	mat->name = NULL;
}

static int	parse_material_3(char **line, int *i, t_material *mat)
{
	if (!ft_strcmp(line[i[0]], "diffuse")
		&& !parse_double(line, i, &mat->k_diffuse))
		return (return_print("Error parsing material diffuse", 0));
	else if (!ft_strcmp(line[i[0]], "shininess")
		&& !parse_double(line, i, &mat->shine))
		return (return_print("Error parsing material shininess", 0));
	else if (!ft_strcmp(line[i[0]], "reflexion")
		&& !parse_double(line, i, &mat->refle))
		return (return_print("Error parsion material reflexion", 0));
	return (1);
}

static int	parse_material_2(char **line, int *i, t_material *mat)
{
	if (!ft_strcmp(line[i[0]], "id"))
	{
		if (line[i[0] + 1] == NULL || !(ft_strlen(line[i[0] + 1]) > 0))
			return (return_print("Error parsing material id", 0));
		else
		{
			if (!(mat->name = ft_strdup(line[++i[0]])))
				return (return_print("malloc error", 0));
			i[1] |= 1;
		}
	}
	else if (!ft_strcmp(line[i[0]], "color")
		&& !parse_color(line, i, &mat->color))
		return (return_print("Error parsing material color", 0));
	else if (!ft_strcmp(line[i[0]], "ambiant")
		&& !parse_double(line, i, &mat->k_ambiant))
		return (return_print("Error parsing material ambiant", 0));
	else if (!ft_strcmp(line[i[0]], "specular")
		&& !parse_double(line, i, &mat->k_spec))
		return (return_print("Error parsing material specular", 0));
	return (parse_material_3(line, i, mat));
}

int			parse_material(t_env *env, char **line)
{
	int			i[2];
	t_material	*mat;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((mat = (t_material *)ft_memalloc(sizeof(t_material))) == NULL ||
		(lst = ft_lstnewfrom(mat, sizeof(*mat))) == NULL)
		return (return_print("malloc error", 0));
	init_material(mat);
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_material_2(line, i, mat) == 0)
			return (0);
	if (env->scene->materials == NULL)
		env->scene->materials = lst;
	else
		ft_lstadd(&(env->scene->materials), lst);
	return (i[1] == 1 ? 1 : return_print("error material imcomplete", 0));
}
