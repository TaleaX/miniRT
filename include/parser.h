/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:53:15 by dns               #+#    #+#             */
/*   Updated: 2023/04/09 17:09:22 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "miniRT.h"

# define LINE printf("\n%s Line %i\nString:\"%s\"\n", __FILE__, __LINE__, line);
# define PARSEFLOATS printf("\n%s Line %i\nParsefloat:%f,%f,%f\n", __FILE__, __LINE__, data()->parse_float[0], data()->parse_float[1], data()->parse_float[2]);


typedef struct s_float
{
	float	sign;
	float	value;
	float	decimal;
}	t_float;

int		parser(int ac, char *av);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_float	init_float_struct(void);
float	parse_float(char *line);
// int		parse_floats(char *line, size_t n_objs, const char *s1, const char *s2);
int		parse_floats(char *line);

// PARSE CHECK
int		check_float(char *line);
int		check_floats(char *line);

// PARSE GET
int		get_sphere(char *line);
int		get_light(char *line);
int		get_ambientlight(char *line);
int		get_plane(char *line);
int		get_cylinder(char *line);
int		get_camera(char *line);
int		get_object(char *line);
int		get_material(char *line, t_obj *object);
int		get_scene(const int fd);

// PARSE SKIP
int		is_space(int x);
int		skip_space(char *input);
char	*parse_skip_three(char *line, t_vec3 *point);
char	*parse_skip_one(char *line, double *f);
char	*parse_skip_color(char *line, t_color *color);

#endif