/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:00:18 by dns               #+#    #+#             */
/*   Updated: 2023/04/18 18:48:46 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_color(t_color color)
{
	printf("%f,%f,%f", color.r * 255, color.g * 255, color.b * 255);
}

void	print_vec3(const char *s1, t_vec3 vec, const char *s2)
{
	printf("%s%f,%f,%f%s", s1, vec.x, vec.y, vec.z, s2);
}

void	print_mfs(t_obj object)
{
	printf("\tMaterial:%u ", object.material);
	printf("Fuzz:%f ", object.fuzz);
	printf("Specular: %f\n", object.specular);
}

void	print_camera(t_camera cam)
{
	print_vec3("C:\t\t", cam.origin, "\t");
	print_vec3("", cam.orientation, "");
	printf("\t\t\t\t\t%f\n", cam.hfov);
}

void	print_ambient(t_light light)
{
	printf("AL:\t\t\t\t\t\t%f\t\t\t", light.intensity);
	print_color(light.color);
	printf("\n");
}
