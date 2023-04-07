/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:53:15 by dns               #+#    #+#             */
/*   Updated: 2023/04/06 21:06:07 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

typedef struct s_float
{
	float	sign;
	float	value;
	float	decimal;
}	t_float;

int			parser(int ac, char *av);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_float		init_float_struct(void);
float		parse_float(char *line);
int			parse_floats(char *line);

#endif