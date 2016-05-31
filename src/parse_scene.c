/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 14:46:26 by lpilotto          #+#    #+#             */
/*   Updated: 2016/05/31 14:53:24 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		parse_scene2(char **line, int *i, t_scene *scene)
{
	if (!ft_strcmp(line[*i], "background"))
	{
		if (!parse_color(line, i, &scene->bgcolor))
			return (return_print("Error parsing scene background color", 0));
	}
	return (1);
}

int				parse_scene(t_env *env, char **line)
{
	t_scene	*scene;
	int		valid;
	int		i;

	if (env->scene != NULL)
	{
		scene = env->scene;
		ft_bzero(scene, sizeof(t_scene));
	}
	else if ((scene = (t_scene *)ft_memalloc(sizeof(t_scene))) == NULL)
		return (return_print("malloc error", 0));
	i = 0;
	valid = 0;
	while (line[++i])
		if (!ft_strcmp(line[i], "ambiant"))
		{
			if (!parse_color(line, &i, &scene->i_ambiant))
				return (return_print("Error parsing scene ambiant light", 0));
			else
				valid |= 1;
		}
		else if (parse_scene2(line, &i, scene) == 0)
			return (0);
	if (valid != 1)
		free(scene);
	else
		env->scene = scene;
	return (valid == 1 ? 1 : return_print("error scene imcomplete", 0));
}
