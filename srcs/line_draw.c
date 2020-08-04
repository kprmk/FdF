/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:35 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/04 21:05:30 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	CRDS
**	x0, y0, x1, y1, z0, z1, col0, col1
*/

void	*line_draw(t_frame *map, int j, int i, int fg)
{
	int	*crds;
	if (!(crds = (int *)malloc(sizeof(int) * 8)))
		return (NULL);
	crds[0] = map->pixs[i][j].x;
	crds[1] = map->pixs[i][j].y;
	crds[2] = map->pixs[(i + ((fg == 0) ? 0 : 1))][(j + ((fg == 0) ? 1 : 0))].x;
	crds[3] = map->pixs[(i + ((fg == 0) ? 0 : 1))][(j + ((fg == 0) ? 1 : 0))].y;
	crds[4] = map->pixs[i][j].z;
	crds[5] = map->pixs[(i + ((fg == 0) ? 0 : 1))][(j + ((fg == 0) ? 1 : 0))].z;
	crds[6] = map->pixs[i][j].col;
	crds[7] = map->pixs[(i + ((fg == 0) ? 0 : 1))][(j + ((fg == 0) ? 1 : 0))].col;
	// crds = projection(crds, map);
	return (bresenham(map, crds));
}

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
**	x, y, dir, accretion, z
**	DATA
**	dx, dy, dxabs, dyabs
*/

void	*bresenham(t_frame *map, int *crds)
{
	int	*data;
	int	*iter;

	if (!(iter = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	if (!(data = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	iter[0] = crds[0];
	iter[1] = crds[1];
	iter[2] = 0;
	iter[3] = 0;
	data[0] = crds[2] - crds[0];
	data[1] = crds[3] - crds[1];
	data[2] = abs(crds[2] - crds[0]);
	data[3] = abs(crds[3] - crds[1]);
	// ft_printf("START################################################\n");
	// ft_printf("%X\t%d %d %d\n", crds[6], (crds[6] >> 16) & 0xff, (crds[6] >> 8) & 0xff, crds[6] & 0xff);
	// ft_printf("%X\t%d %d %d\n", crds[7], (crds[7] >> 16) & 0xff, (crds[7] >> 8) & 0xff, crds[7] & 0xff);
	if (abs(crds[2] - crds[0]) >= abs(crds[3] - crds[1]))
		bresenham_dx(map, crds, iter, data);
	else
		bresenham_dy(map, crds, iter, data);
	free(crds);
	free(iter);
	free(data);
	return (map);
}

/*
**	CRDS
**	x0, y0, x1, y1
**	ITER
**	x, y, dir, accretion, z
**	DATA
**	dx, dy, dxabs, dyabs, col
*/

void	bresenham_dx(t_frame *map, int *crds, int *iter, int *data)
{
	int col;

	iter[2] = diff_direction(data[1]);
	// ft_printf("|%d %d| %d %d %d %d\n", crds[4], crds[5], crds[6], crds[7], data[0], data[1]);
	while ((data[0] > 0) ? iter[0] <= crds[2] : iter[0] >= crds[2])
	{
		col = get_color(crds, iter, data);
		// ft_printf("RES -> %X\t%d %d %d\n", col, (col >> 16) & 0xff, (col >> 8) & 	0xff, col & 0xff);
		mlx_pixel_put(map->mlx, map->win, iter[0], iter[1], col);
		iter[3] += data[3];
		if (iter[3] > data[2])
		{
			iter[3] -= data[2];
			iter[1] += iter[2];
		}
		iter[0] = (data[0] > 0) ? iter[0] + 1 : iter[0] - 1;
	}
	// ft_printf("END###################################################\n");
}

void	bresenham_dy(t_frame *map, int *crds, int *iter, int *data)
{
	int col;

	iter[2] = diff_direction(data[0]);
	// ft_printf("###################################################\n");
	// ft_printf("|%d %d| %d %d\n", crds[4], crds[5], crds[6], crds[7]);	
	while ((data[1] > 0) ? iter[1] <= crds[3] : iter[1] >= crds[3])
	{
		col = get_color(crds, iter, data);
		// ft_printf("!!! %d \n", col);
		mlx_pixel_put(map->mlx, map->win, iter[0], iter[1], col);
		iter[3] += data[2];
		if (iter[3] > data[3])
		{
			iter[3] -= data[3];
			iter[0] += iter[2];
		}
		iter[1] = (data[1] > 0) ? iter[1] + 1 : iter[1] - 1;
	}
	// ft_printf("###################################################\n");
}
