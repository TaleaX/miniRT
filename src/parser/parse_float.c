/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:22:59 by dns               #+#    #+#             */
/*   Updated: 2023/04/20 18:02:51 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_float	init_float_struct(char *line)
{
	t_float	f;

	f.sign = 1.0f;
	f.value = 0.0f;
	f.decimal = 0.1f;
	if (*line == '-')
		f.sign *= -1;
	return (f);
}

float	parse_float(char *line)
{
	t_float	f;

	f = init_float_struct(line);
	if (*line == '-' || *line == '+')
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
	return (f.value *= f.sign);
}

int	parse_floats(char **line)
{
	if (check_floats(*line) < 0)
		return (-1);
	data()->parse_float[0] = parse_float(*line);
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
	if (**line != ',')
		return (-1);
	(*line)++;
	data()->parse_float[1] = parse_float(*line);
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
	if (**line != ',')
		return (-1);
	(*line)++;
	data()->parse_float[2] = parse_float(*line);
	return (0);
}
