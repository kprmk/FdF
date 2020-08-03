/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/03 13:17:09 by kprmk            ###   ########.fr       */
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
		return (crds);
	else if (map->type_proj == 1)
		return (ortographic_isometric(crds, map->angle_iso * M_PI / 180));
	else if (map->type_proj == 2)
		return (ortographic_isometric(crds, 26.57 * M_PI / 180));
	else if (map->type_proj == 3)
		return (ortographic_isometric(crds, 0));
	else
		return (crds);
}

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

int		get_color(int *crds, int *iter, int *data, int flag)
{
	int		red;
	int		green;
	int		blue;
	double	ratio;

	if (!flag)
	{
		ratio = (iter[0] - crds[0]) / (crds[2] - crds[0]);
		// ft_printf("%f\n", (iter[0] - crds[0]) / (crds[2] - crds[0]));
	}
	else
		ratio = (iter[1] - crds[1]) / (crds[3] - crds[1]);
	red = color_formula((data[6] >> 16) & 0xff, (data[7] >> 16) & 0xff, ratio);
	green = color_formula((data[6] >> 8) & 0xff, (data[7] >> 8) & 0xff, ratio);
	blue = color_formula(data[6] & 0xff, data[7] & 0xff, ratio);
	return ((red << 16) | (green << 8) | blue);
}
