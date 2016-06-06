/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:28:02 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/06 17:05:47 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_objenv	set_objenv(t_env *env, t_obj *obj, t_tobj *tobj)
{
	t_objenv	objenv;

	objenv.env = env;
	objenv.obj = obj;
	objenv.tobj = tobj;
	return (objenv);
}
