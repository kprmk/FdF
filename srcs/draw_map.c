/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/24 12:31:47 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		deal_key(int key, t_frame *map)
{
	int	shift;

	shift = 10;
	ft_printf("%d\n", key);
	if (key == 65363)
		map->sh_x += shift;
	if (key == 65362)
		map->sh_y -= shift;
	if (key == 65364)
		map->sh_y += shift;
	if (key == 65361)
		map->sh_x -= shift;
	mlx_clear_window(map->mlx, map->win);
	draw_map(map);
	return (0);
}

/*
**	CRDS
**	x0, y0, x1, y1, z0, z1
*/

int		*isometric(int *crds)
{
	int	x_pr;
	int	y_pr;
	int	x_pr1;
	int	y_pr1;

	x_pr = crds[0];
	y_pr = crds[1];
	x_pr1 = crds[2];
	y_pr1 = crds[3];
	crds[0] = (int)((x_pr - y_pr) * cos(0.523599));
	crds[1] = (int)((x_pr + y_pr) * sin(0.523599) - crds[4]);
	crds[2] = (int)((x_pr1 - y_pr1) * cos(0.523599));
	crds[3] = (int)((x_pr1 + y_pr1) * sin(0.523599) - crds[5]);
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
