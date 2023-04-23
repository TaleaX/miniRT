/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:53:15 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 15:36:28 by dns              ###   ########.fr       */
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

int		parser(int ac, char *av);
int		get_object(char *line, int i);
int		get_scene(const int fd);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

// PARSE CHECK
int		check_float(char *line);
int		check_floats(char *line);

// PARSE FLOAT
// t_float	init_float_struct(void);
float	parse_float(char *line);
int		parse_floats(char **line);

// PARSE GET
int		get_light(char **line, int i);
int		get_ambientlight(char **line, int i);
int		get_camera(char **line, int i);
int		get_sun(char **line, int i);
int		get_resolution(char **line, int i);

int		get_material(char **line, t_obj *object);
int		get_sphere(char **line, int i);
int		get_plane(char **line, int i);
int		get_cylinder(char **line, int i);

// PARSE SKIP
int		is_space(int x);
int		skip_space(char *input);
void	parse_skip_three(char **line, t_vec3 *point);
void	parse_skip_one(char **line, double *f);
void	parse_skip_color(char **line, t_color *color);

// PARSE PRINT
void	print_scene(int i, int j);
void	print_sphere(t_obj sphere);

void	print_color(t_color color);
void	print_vec3(const char *s1, t_vec3 vec, const char *s2);
void	print_mfs(t_obj object);
void	print_camera(t_camera cam);
void	print_ambient(t_light light);

void	print_point_light(t_light light);
void	print_sphere(t_obj sphere);
void	print_plane(t_obj plane);
void	print_cylinder(t_obj cylinder);
void	print_scene(int i, int j);

int		parse_skip_three_err(char **line, t_vec3 *point);
int		parse_skip_one_err(char **line, double *f);
int		parse_skip_color_err(char **line, t_color *color);

#endif