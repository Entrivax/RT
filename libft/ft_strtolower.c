/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:11:43 by lpilotto          #+#    #+#             */
/*   Updated: 2015/12/09 14:50:28 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strtolower(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (*s >= 'A' && *s <= 'Z')
			*s = *s - 'A' + 'a';
		s++;
	}
}
