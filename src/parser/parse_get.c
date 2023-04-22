/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:19:27 by dns               #+#    #+#             */
/*   Updated: 2023/04/22 16:14:00 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_light(char **line)
{
	(*line)++;
	parse_skip_three(line, &data()->lights[data()->n_lights].ray.origin);
	parse_skip_one(line, &data()->lights[data()->n_lights].intensity);
	parse_skip_color(line, &data()->lights[data()->n_lights].color);
	data()->lights[data()->n_lights].type = POINT;
	data()->n_lights++;
	return (0);
}

int	get_ambientlight(char **line)
{
	(*line) += 2;
	parse_skip_one(line, &data()->lights[data()->n_lights].intensity);
	parse_skip_color(line, &data()->lights[data()->n_lights].color);
	data()->lights[data()->n_lights].type = AMBIENT;
	data()->n_lights++;
	return (0);
}

int	get_camera(char **line)
{
	(*line)++;
	parse_skip_three(line, &data()->camera.origin);
	parse_skip_three(line, &data()->camera.orientation);
	parse_skip_one(line, &data()->camera.hfov);
	return (0);
}

int	get_sun(char **line)
{
	(*line)++;
	parse_skip_three(line, &data()->lights[data()->n_lights].ray.direction);
	parse_skip_one(line, &data()->lights[data()->n_lights].intensity);
	parse_skip_color(line, &data()->lights[data()->n_lights].color);
	data()->lights[data()->n_lights].type = SUN;
	data()->n_lights++;
	return (0);
}

int	get_resolution(char **line)
{
	(*line)++;
	parse_skip_one(line, &data()->parse_float[0]);
	data()->width = data()->parse_float[0];
	parse_skip_one(line, &data()->parse_float[1]);
	data()->height = data()->parse_float[1];
	return (0);
}
