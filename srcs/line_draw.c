/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:35 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/21 19:56:17 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		diff_direction(int diff_var)
{
	if (diff_var == 0)
		return (0);
	else if (diff_var > 0)
		return (1);
	else
		return (-1);
}

/*
**	y = k * x + b
**	k - slope -> dy / dx
**	b - intercektion
**
**	-y + dy / dx * x + b = 0
**	-y * dx + dy * x + b * dx = 0
**	A * x + B * y + C = 0
**
**	D = f(x0 + 1, y0 + 0.5) - f(x0, y0) ->
**	A * (x0 + 1) + B * (y0 + 0.5) + C - A(x0) - B(y0) - C = 0
**	A + 0.5 * B = 0 -> dy + 0.5 (-dx) = 0
**	D = -0.5 * dx + dy
**	############################################################
**	CRDS
**	x0, y0, x1, y1
**	ITER
**	x, y, dir, accretion
**	DATA
**	dx, dy, dxabs, dyabs, col
*/

void	*bresenham(frame *map, int *crds, int col)
{
	int	*data;
	int	*iter;

	if (!(iter = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	if (!(data = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	iter[0] = crds[0];
	iter[1] = crds[1];
	iter[2] = 0;
	iter[3] = 0;
	data[0] = crds[2] - crds[0];
	data[1] = crds[3] - crds[1];
	data[2] = abs(crds[2] - crds[0]);
	data[3] = abs(crds[3] - crds[1]);
	data[4] = col;
	if (abs(crds[2] - crds[0]) >= abs(crds[3] - crds[1]))
		return (bresenham_dx(map, crds, iter, data));
	else
		return (bresenham_dy(map, crds, iter, data));
}

/*
**	CRDS
**	x0, y0, x1, y1
**	ITER
**	x, y, dir, accretion
**	DATA
**	dx, dy, dxabs, dyabs, col
*/

void	*bresenham_dx(frame *map, int *crds, int *iter, int *data)
{
	iter[2] = diff_direction(data[1]);
	while ((data[0] > 0) ? iter[0] <= crds[2] : iter[0] >= crds[2])
	{
		mlx_pixel_put(map->mlx, map->win, iter[0], iter[1], data[4]);
		iter[3] += data[3];
		if (iter[3] > data[2])
		{
			iter[3] -= data[2];
			iter[1] += iter[2];
		}
		iter[0] = (data[0] > 0) ? iter[0] + 1 : iter[0] - 1;
	}
	return (NULL);
}

void	*bresenham_dy(frame *map, int *crds, int *iter, int *data)
{
	iter[2] = diff_direction(data[0]);
	while ((data[1] > 0) ? iter[1] <= crds[3] : iter[1] >= crds[3])
	{
		mlx_pixel_put(map->mlx, map->win, iter[0], iter[1], data[4]);
		iter[3] += data[2];
		if (iter[3] > data[3])
		{
			iter[3] -= data[3];
			iter[0] += iter[2];
		}
		iter[1] = (data[1] > 0) ? iter[1] + 1 : iter[1] - 1;
	}
	return (NULL);
}
