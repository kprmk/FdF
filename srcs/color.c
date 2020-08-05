/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 20:29:09 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 20:29:40 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_color_after_comma(const char *str)
{
	unsigned long	res;

	res = 0;
	while (*str != '\0' && *str != ',')
		++str;
	if (*(++str) == '0' && *(++str) == 'x')
	{
		while (*(++str) != '\0')
		{
			if (*str >= 'A' && *str <= 'F')
				res = res * 16 + *str - 'A' + 10;
			else if (*str >= 'a' && *str <= 'f')
				res = res * 16 + *str - 'f' + 10;
			else if (*str >= '0' && *str <= '9')
				res = res * 16 + *str - '0';
			else
				break ;
		}
	}
	else
		return (-1);
	return ((int)res);
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

int		color_formula(int str, int stp, double ratio)
{
	return ((int)((1 - ratio) * str + ratio * stp));
}

int		get_color(int *crds, int *iter, int *data)
{
	int		rd;
	int		gn;
	int		bl;
	double	ratio;

	if (crds[4] == crds[5])
		return (crds[4]);
	if (data[0] > data[1])
		ratio = (iter[0] - crds[0]) / (float)(crds[2] - crds[0]);
	else
		ratio = (iter[1] - crds[1]) / (float)(crds[3] - crds[1]);
	rd = color_formula((crds[4] >> 16) & 0xff, (crds[5] >> 16) & 0xff, ratio);
	gn = color_formula((crds[4] >> 8) & 0xff, (crds[5] >> 8) & 0xff, ratio);
	bl = color_formula(crds[4] & 0xff, crds[5] & 0xff, ratio);
	return ((rd << 16) | (gn << 8) | bl);
}
