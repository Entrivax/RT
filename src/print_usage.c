/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:47:31 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/09 13:34:06 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_usage(char *binary_name)
{
	ft_putendl("Usage: ");
	ft_putstr(binary_name);
	ft_putendl(" [options] <scene_file>");
	ft_putendl("\t-h, -?\tPrint this help message");
	ft_putendl("\t-o\tOutput the render to a file (BMP format!)");
	ft_putendl("\t-t [n]\tUse n threads to compute the image");
	ft_putendl("\t-T\tPrint the render time at the end of the render");
}
