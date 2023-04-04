/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:25:44 by dns               #+#    #+#             */
/*   Updated: 2023/03/30 16:38:01 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	error_handling(int error)
{
	if (error == 1)
		printf("Can't open the file!\n");
	printf("Terminating program...\n");
	exit(EXIT_FAILURE);
}