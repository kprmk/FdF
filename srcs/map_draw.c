/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 19:40:08 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*draw_map(t_frame *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->ht)
	{
		j = 0;
		while (j < map->wh)
		{
			if (j < map->wh - 1)
				if (!line_draw(map, j, i, 0))
					return (NULL);
			if (i < map->ht - 1)
				if (!line_draw(map, j, i, 1))
					return (NULL);
			++j;
		}
		++i;
	}
	return (NULL);
}

/*
**	ISO
**
**	Orthographic Projection
**
**	The most common axonometric projection is an isometric
**	projection where the projection plane intersects each coordinate
**	axis in the model coordinate system at an equal distance.
**
**	CRDS
**	x0, y0, x1, y1, z0, z1
*/

int		*ortographic_isometric(int *crds, double angle)
{
	int		x_pr;
	int		y_pr;
	int		x_pr1;
	int		y_pr1;

	x_pr = crds[0];
	y_pr = crds[1];
	x_pr1 = crds[2];
	y_pr1 = crds[3];
	crds[0] = (int)((x_pr - y_pr) * cos(angle));
	crds[1] = (int)((x_pr + y_pr) * sin(angle) - crds[4]);
	crds[2] = (int)((x_pr1 - y_pr1) * cos(angle));
	crds[3] = (int)((x_pr1 + y_pr1) * sin(angle) - crds[5]);
	return (crds);

}
int		*projection(int *crds, t_frame *map)
{
	if (map->type_proj == 0)
		return (ortographic_isometric(crds, 26.57 * M_PI / 180));
	else if (map->type_proj == 1)
		return (ortographic_isometric(crds, map->angle_iso * M_PI / 180));
	else
		return (crds);
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
