/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 10:43:04 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:50:26 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rm_lst_content(void *elem, size_t s)
{
	(void)s;
	free(elem);
}

void			destruct_env(t_env *env)
{
	if (!env)
		return ;
	if (env->bg_img.img)
		SDL_DestroyTexture(env->bg_img.img);
	env->bg_img.img = NULL;
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	env->renderer = NULL;
	if (env->win)
		SDL_DestroyWindow(env->win);
	env->win = NULL;
	SDL_Quit();
	if (env->scene)
	{
		if (env->scene->camera)
			free(env->scene->camera);
		ft_lstdel(&env->scene->objects, rm_lst_content);
		ft_lstdel(&env->scene->lights, rm_lst_content);
		free(env->scene);
	}
	free(env);
}
