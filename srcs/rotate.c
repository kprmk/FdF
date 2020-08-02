/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:37:21 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 18:12:44 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

// int		*rotate_x_axis(int *crds)
// {
// 	int		x_pr;
// 	int		y_pr;
// 	int		x_pr1;
// 	int		y_pr1;

// 	x_pr = crds[0];
// 	y_pr = crds[1];
// 	x_pr1 = crds[2];
// 	y_pr1 = crds[3];
// 	return (crds);
// }

// int		*rotate_x_axis(int *crds)
// {
// 	int		x_pr;
// 	int		y_pr;
// 	int		x_pr1;
// 	int		y_pr1;

// 	x_pr = crds[0];
// 	y_pr = crds[1];
// 	x_pr1 = crds[2];
// 	y_pr1 = crds[3];
// 	return (crds);
// }

int		*rotate_z_axis(int *crds, double angle)
{
	int		x_pr;
	int		y_pr;
	int		x_pr1;
	int		y_pr1;

	x_pr = crds[0];
	y_pr = crds[1];
	x_pr1 = crds[2];
	y_pr1 = crds[3];
	crds[0] = cos(angle) * x_pr - sin(angle) * y_pr;
	crds[1] = sin(angle) * x_pr + cos(angle) * y_pr;
	crds[2] = cos(angle) * x_pr1 - sin(angle) * y_pr1;
	crds[3] = sin(angle) * x_pr1 + cos(angle) * y_pr1;
	return (crds);
}

int		*rotation_and_shift(int *crds, t_frame *map)
{
	if (map->rotated_axis)
		return (rotate_z_axis(crds, 10 * M_PI / 180));
	crds[0] += map->sh_x;
	crds[1] += map->sh_y;
	crds[2] += map->sh_x;
	crds[3] += map->sh_y;
	map->rotated_axis = 0;
	return (crds);
}