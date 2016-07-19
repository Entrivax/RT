/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:21:39 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/18 18:03:40 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	parse_light_2(char **line, int *i, t_light *light)
{
	if (!ft_strcmp(line[i[0]], "position"))
	{
		if (!parse_vector3(line, i, &light->pos))
			return (return_print("Error parsing light position", 0));
		else
			i[1] |= 1;
	}
	else if (!ft_strcmp(line[i[0]], "color"))
	{
		if (!parse_color(line, i, &light->color))
			return (return_print("Error parsing light color", 0));
		else
			i[1] |= 2;
	}
	else if (!ft_strcmp(line[i[0]], "power"))
	{
		if (!parse_double(line, i, &light->power))
			return (return_print("Error parsing light power", 0));
		else
			i[1] |= 4;
	}
	return (1);
}

int			parse_light(t_env *env, char **line)
{
	int			i[2];
	t_light		*light;
	t_list		*lst;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if ((light = (t_light *)ft_memalloc(sizeof(t_light))) == NULL ||
		(lst = ft_lstnewfrom(light, sizeof(*light))) == NULL)
		return (return_print("malloc error", 0));
	i[0] = 0;
	i[1] = 0;
	while (line[++i[0]])
		if (parse_light_2(line, i, light) == 0)
			return (0);
	if (env->scene->lights == NULL)
		env->scene->lights = lst;
	else
		ft_lstadd(&(env->scene->lights), lst);
	return (i[1] == 7 ? 1 : return_print("error light imcomplete", 0));
}
