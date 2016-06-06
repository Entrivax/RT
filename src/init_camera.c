/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:47:45 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 15:03:07 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init_camera(t_camera *camera)
{
	t_mtx	rot;

	camera->vp_width = camera->res.width > camera->res.height ?
		camera->res.width / (double)camera->res.height : 1;
	camera->vp_height = camera->res.height > camera->res.width ?
		camera->res.height / (double)camera->res.width : 1;
	camera->vp_dist = (ft_max(camera->vp_width, camera->vp_height) / 2.) /
		tan(M_PI * (camera->fov / 2.) / 180.);
	camera->rotx = camera->dir.mtx[0] * M_PI / 180.;
	camera->roty = camera->dir.mtx[1] * M_PI / 180.;
	camera->rotz = camera->dir.mtx[2] * M_PI / 180.;
	set_vector(&camera->dir, 0, 0, 1);
	rot = mtx_createrotmtx(camera->rotx, camera->roty, camera->rotz);
	camera->vp_up_left = mtx_init(4, 1);
	camera->x_indent = mtx_init(4, 1);
	camera->y_indent = mtx_init(4, 1);
	set_vector(&camera->vp_up_left, -camera->vp_width / 2.,
		camera->vp_height / 2., camera->vp_dist);
	set_vector(&camera->x_indent, camera->vp_width / camera->res.width, 0, 0);
	set_vector(&camera->y_indent, 0, -camera->vp_height / camera->res.height, 0);
	camera->dir = mtx_dotproduct(rot, camera->dir);
	camera->x_indent = mtx_dotproduct(rot, camera->x_indent);
	camera->y_indent = mtx_dotproduct(rot, camera->y_indent);
	return (1);
}
