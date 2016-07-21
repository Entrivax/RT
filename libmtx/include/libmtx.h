/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmtx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 13:06:41 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/13 14:33:45 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMTX_H
# define LIBMTX_H

# define SIZE_OF_MTX 16
# define VOM(mTX,x,y) (mTX).mtx[y*(mTX).cols+x]
# define DET(a,b,c,d,e,f,g,h,i) (a*e*i+d*h*c+g*b*f-g*e*c-d*b*i-a*h*f)

typedef struct		s_mtx
{
	int				rows;
	int				cols;
	double			mtx[SIZE_OF_MTX];
}					t_mtx;

t_mtx				mtx_init(int rows, int cols);
t_mtx				mtx_trans(t_mtx mtx);
t_mtx				mtx_dotproduct(t_mtx mtx1, t_mtx mtx2);
double				mtx_dot(t_mtx mtx1, t_mtx mtx2, int a, int b);
t_mtx				mtx_add(t_mtx mtx1, t_mtx mtx2);
t_mtx				mtx_sub(t_mtx mtx1, t_mtx mtx2);
t_mtx				mtx_negate(t_mtx mtx);
t_mtx				mtx_mult(t_mtx mtx, double mult);
t_mtx				mtx_product(t_mtx mtx1, t_mtx mtx2);
t_mtx				mtx_invert(t_mtx mtx);

#endif
