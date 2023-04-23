/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:25:44 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 20:10:15 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	error_handling(int error)
{
	if (error == 1)
		printf("Can't open the file!\n");
	if (error == 2)
		printf("Error while parsing!\n");
	if (error == 3)
		printf("Error\n");
	if (error == 4)
		printf("Error code 4\nSamples Incorrect!");
	printf("Terminating program...\n");
	exit(EXIT_FAILURE);
}
