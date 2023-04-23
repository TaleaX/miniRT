/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:37:41 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 15:23:50 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_space(int x)
{
	return (x == ' ' || x == '\t' || x == '\r' || x == '\f');
}

int	skip_space(char *input)
{
	int	offset;

	offset = 0;
	while (is_space(input[offset]))
		offset++;
	return (offset);
}

void	parse_skip_three(char **line, t_vec3 *point)
{
	(*line) += skip_space(*line);
	if (check_floats(*line) == 0)
	{
		parse_floats(line);
		*point = (t_vec3){data()->parse_float[0], \
		data()->parse_float[1], data()->parse_float[2]};
	}
	else
		*point = (t_vec3){1, 1, 1};
	while ((**line >= '0' && **line <= '9') || \
		**line == '.' || **line == ',' || **line == '-')
			(*line)++;
}

void	parse_skip_one(char **line, double *f)
{
	*line += skip_space(*line);
	if (check_float(*line) == 1)
		*f = parse_float(*line);
	else
		*f = 1;
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
}

void	parse_skip_color(char **line, t_color *color)
{
	*line += skip_space(*line);
	parse_floats(line);
	*color = (t_color){data()->parse_float[0] / 255, \
	data()->parse_float[1] / 255, data()->parse_float[2] / 255, 1.0f};
	while ((**line >= '0' && **line <= '9') || \
	**line == '.' || **line == ',' || **line == '-')
		(*line)++;
}
