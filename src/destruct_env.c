/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 10:43:04 by lpilotto          #+#    #+#             */
/*   Updated: 2016/09/06 14:56:57 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rm_lst_content(void *elem, size_t s)
{
	(void)s;
	free(elem);
}

static void		rm_lst_material(void *elem, size_t s)
{
	(void)s;
	free(((t_material *)elem)->name);
	free(elem);
}

static void		exit_threads(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->n_threads)
		if (env->threads[i])
			pthread_cancel(env->threads[i]);
	if (env->clockthread)
	{
		pthread_cancel(env->clockthread);
		pthread_join(env->clockthread, NULL);
	}
	i = -1;
	while (++i < env->n_threads)
		if (env->threads[i])
			pthread_join(env->threads[i], NULL);
}

void			clean_scene(t_scene *scene)
{
	if (scene->camera)
		free(scene->camera);
	ft_lstdel(&scene->objects, rm_lst_content);
	ft_lstdel(&scene->lights, rm_lst_content);
	ft_lstdel(&scene->materials, rm_lst_material);
	free(scene);
}

void			destruct_env(t_env *env)
{
	if (!env)
		return ;
	exit_threads(env);
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
		clean_scene(env->scene);
	free(env);
}
