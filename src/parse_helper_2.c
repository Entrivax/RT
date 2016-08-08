/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:08:38 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:55:20 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				parse_mtx_trans(char **line, int *i, t_mtx *v)
{
	if (line[*i + 1] == NULL || line[*i + 2] == NULL ||
		line[*i + 3] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]) || !ft_isnumber(line[*i + 2]) ||
		!ft_isnumber(line[*i + 3]))
		return (0);
	*v = mtx_init(4, 4);
	v->mtx[3] = ft_atof(line[*i + 1]);
	v->mtx[7] = ft_atof(line[*i + 2]);
	v->mtx[11] = ft_atof(line[*i + 3]);
	v->mtx[0] = 1;
	v->mtx[5] = 1;
	v->mtx[10] = 1;
	v->mtx[15] = 1;
	*i += 3;
	return (1);
}

int				parse_mtx_rot(char **line, int *i, t_mtx *v)
{
	double	rotx;
	double	roty;
	double	rotz;

	if (line[*i + 1] == NULL || line[*i + 2] == NULL ||
		line[*i + 3] == NULL)
		return (0);
	if (!ft_isnumber(line[*i + 1]) || !ft_isnumber(line[*i + 2]) ||
		!ft_isnumber(line[*i + 3]))
		return (0);
	rotx = ft_atof(line[*i + 1]) * M_PI / 180.;
	roty = ft_atof(line[*i + 2]) * M_PI / 180.;
	rotz = ft_atof(line[*i + 3]) * M_PI / 180.;
	*v = mtx_createrotmtx(rotx, roty, rotz);
	*i += 3;
	return (1);
}
