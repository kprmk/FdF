/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:44:43 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/23 11:50:17 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_formula(int str, int stp, double ratio)
{
	return ((int)((1 - ratio) * str + ratio * stp));
}

/*
**	cur - current coord, str - start, stp - stop, dif - difference
**	##############################################################
**	CRDS
**	x0, y0, x1, y1
**	ITER
**	x, y, dir, accretion
**	DATA
**	dx, dy, dxabs, dyabs, col0, col1
*/

int		get_color(int* crds, int *iter, int *data, int flag)
{
	int		R;
	int		G;
	int		B;
	double	ratio;

	if (!flag)
		ratio = (iter[0] - crds[0]) / (crds[2] - crds[0]);
	else
		ratio = (iter[1] - crds[1]) / (crds[3] - crds[1]);
	// ft_printf("## %d\n", ratio);
	R = color_formula((data[4] >> 16) & 0xff, (data[5] >> 16) & 0xff, ratio);
	G = color_formula((data[4] >> 8) & 0xff, (data[5] >> 8) & 0xff, ratio);
	B = color_formula(data[4] & 0xff, data[5] & 0xff, ratio);
	return ((R << 16) | (G << 8) | B);
}
