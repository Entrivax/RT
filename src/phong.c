/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:41:32 by lpilotto          #+#    #+#             */
/*   Updated: 2016/07/19 14:25:46 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define DOTVB(a, b, n) (a.mtx[n] * b.mtx[n])
#define DOTV(a, b) (a.mtx[0]*b.mtx[0] + a.mtx[1]*b.mtx[1] + a.mtx[2]*b.mtx[2])

#include <stdio.h>
void		phong(t_phpa *ph)
{
	t_obj	*obj;
	double	dln;
	double	dotrv;
	double	p;
	t_ray	inv[2];
	t_mtx	r;

	p = ph->light->power / POW2(ph->lray->t);
	printf("P: %lf\n", p);
	inv[0] = invert_ray(*ph->lray);
	printf("Light invert: %lf; %lf; %lf\n", inv[0].dir.mtx[0], inv[0].dir.mtx[1], inv[0].dir.mtx[2]);
	printf("NORMAL: %lf; %lf; %lf\n", ph->normal.mtx[0], ph->normal.mtx[1], ph->normal.mtx[2]);
	obj = ph->ray->closest;
	dln = ft_fclamp(fabs(DOTV(ph->normal, inv[0].dir)), 0, 1);
	printf("dln: %lf\n", dln);
	printf("res: %lf + %lf + %lf\n", DOTVB(ph->normal, inv[0].dir, 0), DOTVB(ph->normal, inv[0].dir, 1), DOTVB(ph->normal, inv[0].dir, 2));
	r = norm_vect(mtx_sub(mtx_mult(ph->normal, 2 * dln), inv[0].dir));
	inv[1] = invert_ray(*ph->ray);
	dotrv = ft_fclamp(pow(DOTV(r, inv[1].dir), obj->shine), 0, 1);
	rgb_add(ph->diffuse, ft_max(ph->light->color.r * obj->color.r * obj->k_diffuse * dln * p, 0),
		ft_max(ph->light->color.g * obj->color.g * obj->k_diffuse * dln * p, 0),
		ft_max(ph->light->color.b * obj->color.b * obj->k_diffuse * dln * p, 0));
	rgb_add(ph->specular, ft_max(ph->light->color.r * obj->k_spec * dotrv * p, 0),
		ft_max(ph->light->color.g * obj->k_spec * dotrv * p, 0),
		ft_max(ph->light->color.b * obj->k_spec * dotrv * p, 0));
}
