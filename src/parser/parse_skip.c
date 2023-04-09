/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:37:41 by dns               #+#    #+#             */
/*   Updated: 2023/04/09 17:10:24 by dns              ###   ########.fr       */
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

char	*parse_skip_three(char *line, t_vec3 *point)
{
	line += skip_space(line);
	parse_floats(line);
	*point = (t_vec3){data()->parse_float[0], \
	data()->parse_float[1], data()->parse_float[2]};
	while ((*line >= '0' && *line <= '9') || \
	*line == '.' || *line == ',' || *line == '-')
		line++;
	return (line);
}

char	*parse_skip_one(char *line, double *f)
{
	line += skip_space(line);
	*f = parse_float(line);
	while ((*line >= '0' && *line <= '9') || *line == '.' || *line == '-')
		line++;
	return (line);
}

char	*parse_skip_color(char *line, t_color *color)
{
	line += skip_space(line);
	parse_floats(line);
	*color = (t_color){data()->parse_float[0] / 255, \
	data()->parse_float[1] / 255, data()->parse_float[2] / 255, 1.0f};
	while ((*line >= '0' && *line <= '9') || \
	*line == '.' || *line == ',' || *line == '-')
		line++;
	return (line);
}
