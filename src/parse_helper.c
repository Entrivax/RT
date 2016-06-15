/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 12:53:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/15 12:38:57 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				parse_resolution(char **line, int *i, t_res *res)
{
	if (line[*i + 1] == NULL || line[*i + 2] == NULL ||
		line[*i + 3] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]) || !ft_isnumber(line[*i + 2]))
		return (0);
	res->width = ft_atoi(line[*i + 1]);
	res->height = ft_atoi(line[*i + 2]);
	*i += 2;
	if (res->width < 50 || res->height < 10)
		return (0);
	return (1);
}

int				parse_vector3(char **line, int *i, t_mtx *v)
{
	if (line[*i + 1] == NULL || line[*i + 2] == NULL ||
		line[*i + 3] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]) || !ft_isnumber(line[*i + 2]) ||
		!ft_isnumber(line[*i + 3]))
		return (0);
	*v = mtx_init(4, 1);
	v->mtx[0] = ft_atof(line[*i + 1]);
	v->mtx[1] = ft_atof(line[*i + 2]);
	v->mtx[2] = ft_atof(line[*i + 3]);
	v->mtx[3] = 1;
	*i += 3;
	return (1);
}

int				parse_color(char **line, int *i, t_rgb *rgb)
{
	if (line[*i + 1] == NULL || line[*i + 2] == NULL ||
		line[*i + 3] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]) || !ft_isnumber(line[*i + 2]) ||
		!ft_isnumber(line[*i + 3]))
		return (0);
	rgb->r = ft_fclamp(ft_atof(line[*i + 1]), 0, 1);
	rgb->g = ft_fclamp(ft_atof(line[*i + 2]), 0, 1);
	rgb->b = ft_fclamp(ft_atof(line[*i + 3]), 0, 1);
	*i += 3;
	return (1);
}

int				parse_double(char **line, int *i, double *a)
{
	if (line[*i + 1] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]))
		return (0);
	*a = ft_atof(line[*i + 1]);
	*i += 1;
	return (1);
}
