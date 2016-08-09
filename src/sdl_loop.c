/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 10:41:49 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/09 11:26:33 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	execute_queue(t_env *env)
{
	t_list		*tmp;
	void		(*method)(t_env *env);

	pthread_mutex_lock(&env->queuemutex);
	tmp = env->queue;
	while (tmp)
	{
		method = (void (*)(t_env *env))tmp->content;
		if (method != NULL)
			method(env);
		tmp = env->queue->next;
		free(env->queue);
	}
	env->queue = NULL;
	pthread_mutex_unlock(&env->queuemutex);
}

void		sdl_loop(t_env *env)
{
	SDL_Event	event;

	env->loop = 1;
	while (env->loop)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break ;
		pthread_mutex_lock(&env->bg_img.mutex);
		SDL_SetRenderTarget(env->renderer, NULL);
		SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 0);
		SDL_RenderClear(env->renderer);
		SDL_RenderCopy(env->renderer, env->bg_img.img, NULL, NULL);
		SDL_RenderPresent(env->renderer);
		pthread_mutex_unlock(&env->bg_img.mutex);
		execute_queue(env);
		SDL_Delay(10);
	}
}
