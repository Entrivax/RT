/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:58 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/15 17:11:18 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		compute_light(t_scene *scene, t_ray *ray)
{
	t_list	*current;
	t_ray	lray;
	t_rgb	color;
	
	current = scene->lights;
	color = 
	while (current)
	{
		lray.pos = mtx_mult(((t_light *)current->content)->pos);
		lray.dir = norm_vect(mtx_sub(mtx_mult(ray.dir, ray->t), lray.pos));
		if (find_closest(scene, &lray) && ray->closest == lray.closest)
		{
			
		}
		current = current->next;
	}
}
