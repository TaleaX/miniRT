/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skip2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 03:40:19 by dantonik          #+#    #+#             */
/*   Updated: 2023/04/23 20:59:36 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_skip_three_err(char **line, t_vec3 *point)
{
	(*line) += skip_space(*line);
	if (check_floats(*line) == 0)
	{
		parse_floats(line);
		*point = (t_vec3){data()->parse_float[0], \
		data()->parse_float[1], data()->parse_float[2]};
	}
	else
		return (1);
	while ((**line >= '0' && **line <= '9') || \
		**line == '.' || **line == ',' || **line == '-')
			(*line)++;
	return (0);
}

int	parse_skip_one_err(char **line, double *f)
{
	*line += skip_space(*line);
	if (check_float(*line) == 1)
		*f = parse_float(*line);
	else
		return (1);
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
	return (0);
}

int	parse_skip_color_err(char **line, t_color *color)
{
	*line += skip_space(*line);
	if (check_floats(*line) == 0)
	{
		parse_floats(line);
		*color = (t_color){data()->parse_float[0] / 255, \
		data()->parse_float[1] / 255, data()->parse_float[2] / 255, 1.0f};
	}
	else
		return (1);
	if (data()->parse_float[0] < 0 || data()->parse_float[0] > 255)
		return (printf("Color must be between 0 and 255!\n"), 1);
	if (data()->parse_float[1] < 0 || data()->parse_float[1] > 255)
		return (printf("Color must be between 0 and 255!\n"), 1);
	if (data()->parse_float[2] < 0 || data()->parse_float[2] > 255)
		return (printf("Color must be between 0 and 255!\n"), 1);
	while ((**line >= '0' && **line <= '9') || \
	**line == '.' || **line == ',' || **line == '-')
		(*line)++;
	return (0);
}
