/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:19:27 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 16:53:34 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_light(char **line, int i)
{
	(*line)++;
	i += parse_skip_three_err(line, \
		&data()->lights[data()->n_lights].ray.origin);
	i += parse_skip_one_err(line, &data()->lights[data()->n_lights].intensity);
	i += parse_skip_color_err(line, &data()->lights[data()->n_lights].color);
	if (i > 0)
		return (-1);
	data()->b_light = true;
	data()->lights[data()->n_lights].type = POINT;
	data()->n_lights++;
	return (0);
}

int	get_ambientlight(char **line, int i)
{
	(*line) += 2;
	i += parse_skip_one_err(line, &data()->lights[data()->n_lights].intensity);
	i += parse_skip_color_err(line, &data()->lights[data()->n_lights].color);
	if (i > 0)
		return (-1);
	data()->b_light = true;
	data()->lights[data()->n_lights].type = AMBIENT;
	data()->n_lights++;
	return (0);
}

int	get_camera(char **line, int i)
{
	(*line)++;
	i += parse_skip_three_err (line, &data()->camera.origin);
	i += parse_skip_three_err(line, &data()->camera.orientation);
	i += parse_skip_one_err(line, &data()->camera.hfov);
	if (i > 0)
		return (-1);
	return (0);
}

int	get_sun(char **line, int i)
{
	(*line)++;
	i += parse_skip_three_err(line, \
		&data()->lights[data()->n_lights].ray.direction);
	i += parse_skip_one_err(line, &data()->lights[data()->n_lights].intensity);
	i += parse_skip_color_err(line, &data()->lights[data()->n_lights].color);
	if (i > 0)
		return (-1);
	data()->b_light = true;
	data()->lights[data()->n_lights].type = SUN;
	data()->n_lights++;
	return (0);
}

int	get_resolution(char **line, int i)
{
	(*line)++;
	i += parse_skip_one_err(line, &data()->parse_float[0]);
	data()->width = data()->parse_float[0];
	i += parse_skip_one_err(line, &data()->parse_float[1]);
	data()->height = data()->parse_float[1];
	if (i > 0)
		return (-1);
	return (0);
}
