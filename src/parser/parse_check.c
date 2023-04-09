/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:48:51 by dns               #+#    #+#             */
/*   Updated: 2023/04/09 15:32:35 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_floats(char *line)
{
	if (check_float(line) != 2)
		return (-1);
	line += skip_space(line);
	if (*line == '-' || *line == '+')
		line++;
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	line++;
	if (check_float(line) != 2)
		return (-1);
	line += skip_space(line);
	if (*line == '-' || *line == '+')
		line++;
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	line++;
	if (check_float(line) != 1)
		return (-1);
	return (0);
}

int	check_float(char *line)
{
	line += skip_space(line);
	if (*line == '-' || *line == '+')
		line++;
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '.')
		line++;
	else if (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\0')
		return (1);
	else if (*line == ',')
		return (2);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\0')
		return (1);
	if (*line == ',')
		return (2);
	return (0);
}
