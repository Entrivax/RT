/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:09:33 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/17 16:41:17 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "quadric_shortcuts.h"

double		find_dist(t_ray ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	int		ret;
	t_mtx	mtxs[2];

	mtxs[0] = ray.pos;//mtx_product(obj->i_trans, ray.pos);
	mtxs[1] = ray.dir;//mtx_product(obj->i_trans, ray.dir);
	/*abc[0] = AX * POW2(XD) + EX * POW2(YD) + HX * POW2(ZD)
		+ 2 * (BX * XD * YD + CX * XD * ZD + FX * YD * ZD);
	abc[1] = 2 * (AX * XO * XD + BX * (XO * YD + XD * YO)
		+ CX * (XO * ZD + XD * ZO) + DX * XD + EX * YO * YD
		+ FX * (YO * ZD + YD * ZO) + GX * YD + HX * ZO * ZD + IX * ZD);
	abc[2] = AX * POW2(XO) + EX * POW2(YO) + HX * POW2(ZO)
		+ 2 * (BX * XO * YO + CX * XO * ZO + DX * XO + FX * YO * ZO
		+ GX * YO + IX * ZO) + JX;*/
	abc[0] = AX * POW2(XD) + BX * POW2(YD) + CX * POW2(ZD) + DX * XD * YD
		+ EX * XD * ZD + FX * YD * ZD;
	abc[1] = 2 * (AX * XO * XD + BX * YO * YD + CX * ZO * ZD)
		+ DX * (XO * YD + YO * XD) + EX * (XO * ZD + ZO * XD)
		+ FX * (YO * ZD + ZO * YD) + GX * XD + HX * YD + IX * ZD;
	abc[2] = AX * POW2(XO) + BX * POW2(YO) + CX * POW2(ZO)
		+ DX * XO * YO + EX * XO * ZO + FX * YO * ZO
		+ GX * XO + HX * YO + IX * ZO + JX;
	if ((ret = solve_quadratic(abc, t, t + 1)) == 0)
		return (-1);
	if (ret == 1)
		return (t[0]);
	if ((t[0] < t[1] || t[1] <= LIMIT_MIN) && t[0] > LIMIT_MIN)
		return (t[0]);
	else if (t[1] > LIMIT_MIN)
		return (t[1]);
	return (-1);
}
