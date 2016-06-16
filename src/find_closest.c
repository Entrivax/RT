/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:58:52 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/16 14:56:52 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	find_closest(t_scene *scene, t_ray *ray)
{
	t_list	*current;
	double	t;

	ray->closest = NULL;
	current = scene->objects;
	while (current)
	{
		if ((t = find_dist(*ray, (t_obj *)current->content)) > LIMIT_MIN
			&& (t < ray->t || ray->closest == NULL))
		{
			ray->t = t;
			ray->closest = (t_obj *)current->content;
		}
		current = current->next;
	}
	return (ray->closest != NULL);
}