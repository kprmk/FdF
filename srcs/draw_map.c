/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 14:26:30 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		deal_key(int key, t_frame *map)
{
	ft_printf("%d\n", key);
	if (key == 65363)
		map->sh_x += map->sh_step;
	if (key == 65362)
		map->sh_y -= map->sh_step;
	if (key == 65364)
		map->sh_y += map->sh_step;
	if (key == 65361)
		map->sh_x -= map->sh_step;
	mlx_clear_window(map->mlx, map->win);
	draw_map(map);
	return (0);
}

int		*projection(int *crds, int type_proj)
{
	if (type_proj == 1)
		return (crds);
	else if (type_proj == 2)
		return (isometric(crds, 30 * M_PI / 180));
	else
		return (isometric(crds, 45 * M_PI / 180));
}

/*
**	Oblique Projection
**
**	The Cabinet projection makes 63.4° angle with the projection plane. **	In Cabinet projection, lines perpendicular to the viewing surface are **	projected at ½ their actual length
**
**	CRDS
**	x0, y0, x1, y1, z0, z1
*/

int		*isometric(int *crds, double angle)
{
	int		x_pr;
	int		y_pr;
	int		x_pr1;
	int		y_pr1;

	x_pr = crds[0];
	y_pr = crds[1];
	x_pr1 = crds[2];
	y_pr1 = crds[3];
	// ft_printf("%f", angle);
	crds[0] = (int)((x_pr - y_pr) * cos(angle));
	crds[1] = (int)((x_pr + y_pr) * sin(angle) - crds[4]);
	crds[2] = (int)((x_pr1 - y_pr1) * cos(angle));
	crds[3] = (int)((x_pr1 + y_pr1) * sin(angle) - crds[5]);
	return (crds);
}

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
