/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:01:40 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 16:50:28 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_mlx_hooks(t_env *env)
{
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, expose_hook, env);
}
