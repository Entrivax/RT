/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 10:01:56 by exam              #+#    #+#             */
/*   Updated: 2016/08/10 09:53:38 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void				print_hexa(const char c)
{
	char		*tab;

	tab = "0123456789abcdef";
	write(1, tab + ((c >> 4) & 0xf), 1);
	write(1, tab + (c & 0xf), 1);
}

const char			*writable_char(const char *c)
{
	const char	*dot;

	dot = (const char *)".";
	if (*c < 32 || *c > 126)
		return (dot);
	return (c);
}

void				print_writable(const char *ptr, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		write(1, writable_char(ptr + i), 1);
		i++;
	}
	write(1, "\n", 1);
}

void				print_memory(const void *addr, size_t size)
{
	const char	*ptr;
	size_t		i;
	size_t		tmp;

	ptr = (const char *)addr;
	i = 0;
	while (i < size)
	{
		print_hexa(*(ptr + i));
		if (i % 2 == 1)
			write(1, " ", 1);
		if (i % 16 == 15)
			print_writable(ptr + i - 15, 16);
		i++;
	}
	tmp = i;
	while (i % 16 != 0)
	{
		write(1, "  ", 2);
		if (i % 2 == 1)
			write(1, " ", 1);
		if (i % 16 == 15)
			print_writable(ptr + tmp - tmp % 16, tmp % 16);
		i++;
	}
}
