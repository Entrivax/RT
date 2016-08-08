/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_title.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 13:44:36 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/08 13:50:05 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	update_title(t_env *env)
{
	SDL_SetWindowTitle(env->win, env->new_title);
}
