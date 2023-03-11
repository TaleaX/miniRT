/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:01:37 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 16:59:38 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COLOR_H
# define COLOR_H
# include <stdlib.h>
# include <stdint.h>
# include "vector.h"

uint32_t	get_rgba(t_color color);
uint32_t	get_color_t(double t);
t_color		get_color(double light, t_color color_obj);

#endif