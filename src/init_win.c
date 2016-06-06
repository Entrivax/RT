/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:44:57 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 16:49:43 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init_win(t_env *env)
{
	if ((env->win = mlx_new_window(env->mlx, env->scene->camera->res.width,
		env->scene->camera->res.height, "rtv1 @42")) == NULL)
		return (-1);
	return (0);
}
