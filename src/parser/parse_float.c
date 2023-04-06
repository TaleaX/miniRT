/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:22:59 by dns               #+#    #+#             */
/*   Updated: 2023/04/05 14:00:19 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// typedef struct s_float
// {
// 	float	sign;			// 1.0f
// 	float	value;			// 0.0f
// 	float	decimal;		// 0.1f
// }	t_float;

t_float	init_float_struct(void)
{
	t_float	f;

	f.sign = 1.0f;
	f.value = 0.0f;
	f.decimal = 0.1f;
	return (f);
}

float	parse_float(char *line, t_float f)
{
	f = init_float_struct();
	if (*line == '-')
	{
		f.sign *= -1;
		line++;
	}
	else if (*line == '+')
		line++;
	while (*line >= '0' && *line <= '9')
	{
		f.value = (f.value * 10.0f) + (float)(*line - '0');
		line++;
	}
	if (*line == '.')
	{
		line++;
		while (*line >= '0' && *line <= '9')
		{
			f.value += f.decimal * (float)(*line - '0');
			f.decimal *= 0.1f;
			line++;
		}
	}
	f.value *= f.sign;
	return (1.0f);
}
