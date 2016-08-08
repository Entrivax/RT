/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 13:28:24 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:54:08 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	invert_ray(t_ray ray)
{
	t_ray	inverted;

	inverted.pos = mtx_add(ray.pos, mtx_mult(ray.dir, ray.t));
	inverted.t = ray.t;
	inverted.dir = mtx_negate(ray.dir);
	return (inverted);
}
