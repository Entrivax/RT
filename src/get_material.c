/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 10:27:24 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/12 14:39:43 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_material	*get_material(t_env *env, const char *id)
{
	t_list	*material;

	material = env->scene->materials;
	while (material)
	{
		if (!ft_strcmp(id, ((t_material *)material->content)->name))
			return (((t_material *)material->content));
		material = material->next;
	}
	return (&env->base_material);
}
