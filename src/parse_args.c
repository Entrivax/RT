/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 12:24:06 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/10 12:54:11 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>

char	ft_strstartwith(char *str, char *start)
{
	while (ft_isspace(*str))
		str++;
	while (*start)
	{
		if (*start != *str)
			return (0);
		start++;
		str++;
	}
	return (1);
}

int		parse_arg(t_env *env, int argc, int *i, char **argv)
{
	if (ft_strstartwith(argv[*i], "-t") && *i + 1 < argc)
	{
		if (!parse_int(argv, i, &env->n_threads))
			return (return_print("Error parsing -t [n]", -1));
		else if (env->n_threads <= 0)
			return (return_print("Number of threads can't be below 1!", -1));
	}
	else if (ft_strstartwith(argv[*i], "-T"))
		env->print_time = 1;
	else if (ft_strstartwith(argv[*i], "-h") || ft_strstartwith(argv[*i], "-?"))
		print_usage(argv[0]);
	else if (ft_strstartwith(argv[*i], "-o"))
	{
		if (env->fd != 0)
			return (return_print("One file at time!", -1));
		if ((env->fd = open(argv[++*i], O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0)
			return (return_print("Failed to open file!", -1));
	}
	else
	{
		ft_putendl("Unknown parameter : ");
		return (return_print(argv[*i], -1));
	}
	return (0);
}

int		parse_args(t_env *env, int argc, char **argv)
{
	int		i;
	int		file_parsed;

	i = 0;
	file_parsed = -1;
	while (++i < argc)
	{
		if (ft_strstartwith(argv[i], "-"))
		{
			if (parse_arg(env, argc, &i, argv) == -1)
				return (-1);
		}
		else if (i == argc - 1)
		{
			if (parse_file(env, argv[i]) == -1)
				return (-1);
			else
				file_parsed = 0;
		}
	}
	return (file_parsed);
}
