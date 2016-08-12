/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 12:35:59 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/11 11:13:20 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	delete_line_array(char **line, int return_state)
{
	char	**oline;

	oline = line;
	while (*line)
	{
		free(*line);
		line++;
	}
	free(oline);
	return (return_state);
}

static int	parse_line(t_env *env, char **line)
{
	if (!ft_strcmp(line[0], "scene"))
		return (delete_line_array(line, parse_scene(env, line)));
	else if (!ft_strcmp(line[0], "camera"))
		return (delete_line_array(line, parse_camera(env, line)));
	else if (!ft_strcmp(line[0], "sphere"))
		return (delete_line_array(line, parse_sphere(env, line)));
	else if (!ft_strcmp(line[0], "plane"))
		return (delete_line_array(line, parse_plane(env, line)));
	else if (!ft_strcmp(line[0], "cylinder"))
		return (delete_line_array(line, parse_cylinder(env, line)));
	else if (!ft_strcmp(line[0], "cone"))
		return (delete_line_array(line, parse_cone(env, line)));
	else if (!ft_strcmp(line[0], "light"))
		return (delete_line_array(line, parse_light(env, line)));
	else if (!ft_strcmp(line[0], "material"))
		return (delete_line_array(line, parse_material(env, line)));
	ft_putstr("Unknown type : ");
	ft_putendl(line[0]);
	return (delete_line_array(line, 0));
}

static int	parse_error(int line_nbr)
{
	ft_putstr("error processing line ");
	ft_putnbr(line_nbr);
	ft_putendl("\nexiting...");
	return (-1);
}

int			parse_file(t_env *env, char *file)
{
	char	*line;
	char	**str;
	int		l;
	int		fd;

	line = NULL;
	l = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (return_print("error while opening the file", -1));
	while (get_next_line(fd, &line) > 0)
	{
		++l;
		str = ft_strsplit(line, ' ');
		if (*str == NULL || ft_strlen(*str) == 0 || !ft_strncmp(*str, "--", 2))
		{
			delete_line_array(str, 0);
			free(line);
			continue ;
		}
		if (!parse_line(env, str))
			return (parse_error(l));
		free(line);
	}
	close(fd);
	return (env->scene && env->scene->camera ? 0 : -1);
}
