/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:44:57 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:50:45 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_win(t_env *env)
{
	if (SDL_CreateWindowAndRenderer(env->scene->camera->res.width,
		env->scene->camera->res.height, SDL_WINDOW_SHOWN, &env->win,
		&env->renderer))
		return (-1);
	SDL_SetWindowTitle(env->win, "rt @42");
	return (0);
}
