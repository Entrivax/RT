/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:10:54 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/21 12:28:08 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		parse_camera_2(char **line, int *i, t_env *env, int *valid)
{
	if (!ft_strcmp(line[*i], "position"))
	{
		if (!parse_vector3(line, i, &env->scene->camera->pos))
			return (return_print("Error parsing camera position", 0));
		else
			*valid |= 2;
	}
	else if (!ft_strcmp(line[*i], "rotation"))
	{
		if (!parse_vector3(line, i, &env->scene->camera->dir))
			return (return_print("Error parsing camera rotation", 0));
		else
			*valid |= 4;
	}
	else if (!ft_strcmp(line[*i], "fov"))
	{
		if (!parse_double(line, i, &env->scene->camera->fov))
			return (return_print("Error parsing camera field of view", 0));
		else
			*valid |= 8;
	}
	else if (!ft_strcmp(line[*i], "antialiasing"))
	{
		if (!parse_int(line, i, &env->scene->camera->antialiasing))
			return (return_print("Error parsing camera antialiasing", 0));
		if (env->scene->camera->antialiasing <= 0)
			return (return_print(
				"Error antialiasing must be superior to 0", 0));
	}
	return (1);
}

int				parse_camera(t_env *env, char **line)
{
	int				i;
	int				valid;

	if (env->scene == NULL)
		return (return_print("Error, a scene must be declared first", 0));
	if (env->scene->camera == NULL && (env->scene->camera =
		(t_camera *)ft_memalloc(sizeof(t_camera))) == NULL)
		return (return_print("malloc error", 0));
	i = 0;
	valid = 0;
	env->scene->camera->antialiasing = 1;
	while (line[++i])
	{
		if (!ft_strcmp(line[i], "screen"))
		{
			if (!parse_resolution(line, &i, &env->scene->camera->res))
				return (return_print("Error parsing camera resolution", 0));
			else
				valid |= 1;
		}
		else if (parse_camera_2(line, &i, env, &valid) == 0)
			return (0);
	}
	return (valid == 15 && (init_camera(env->scene->camera)));
}
