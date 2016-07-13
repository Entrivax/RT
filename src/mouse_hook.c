/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 15:51:08 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/13 15:21:08 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <stdio.h>
int		mouse_hook(int button, int x, int y, t_env *env)
{
	t_ray	ray;
	t_ray	lray;
	t_mtx	nor;
	t_mtx	inter;

	(void)button;
	ray.dir = norm_vect(mtx_add(env->scene->camera->dir, mtx_add(mtx_mult(env->
		scene->camera->x_indent, x - env->scene->camera->res.width / 2), mtx_mult(
		env->scene->camera->y_indent, y - env->scene->camera->res.height / 2))));
	ray.pos = env->scene->camera->pos;
	printf("Ray dir: (%lf; %lf; %lf)\n", ray.dir.mtx[0], ray.dir.mtx[1], ray.dir.mtx[2]);
	printf("Ray pos: (%lf; %lf; %lf)\n", ray.pos.mtx[0], ray.pos.mtx[1], ray.pos.mtx[2]);
	if (find_closest(env->scene, &ray))
	{
		printf("Ray length: %lf\n", ray.t);
		printf("Object: %p\n", ray.closest);
		inter = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);
		nor = get_normal(ray);
		printf("Intersection: (%lf; %lf; %lf)\n", inter.mtx[0], inter.mtx[1], inter.mtx[2]);
		printf("Normal: (%lf; %lf; %lf)\n", nor.mtx[0], nor.mtx[1], nor.mtx[2]);
		if (env->scene->lights)
		{
			printf("Test first light:\n");
			lray.pos = ((t_light *)env->scene->lights->content)->pos;
			lray.dir = norm_vect(mtx_add(mtx_sub(mtx_mult(ray.dir, ray.t),
				lray.pos), ray.pos));
			printf("Light dir: (%lf; %lf; %lf)\n", lray.dir.mtx[0], lray.dir.mtx[1], lray.dir.mtx[2]);
			printf("Light pos: (%lf; %lf; %lf)\n", lray.pos.mtx[0], lray.pos.mtx[1], lray.pos.mtx[2]);
			if (find_closest(env->scene, &lray))
			{
				inter = mtx_add(mtx_mult(ray.dir, ray.t), ray.pos);	
				printf("Light ray length: %lf\n", lray.t);
				printf("Object: %p\n", lray.closest);
				printf("Intersection: (%lf; %lf; %lf)\n", inter.mtx[0], inter.mtx[1], inter.mtx[2]);
			}
		}
	}
	else
		printf("No object found!\n");
	printf("\n");
	return (1);
}
