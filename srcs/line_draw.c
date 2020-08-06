/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:35 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 14:31:20 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	CRDS
**	x0, y0, x1, y1, col0, col1
*/

void	*line_draw(t_frame *map, int j, int i, int fg)
{
	int	*crds;

	if (!(crds = (int *)malloc(sizeof(int) * 6)))
		return (NULL);
	if (map->type_proj == 0)
	{
		crds[0] = map->pixs[i][j].x;
		crds[1] = map->pixs[i][j].y;
		crds[2] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].x;
		crds[3] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].y;
		crds[4] = map->pixs[i][j].col;
		crds[5] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].col;
	}
	else
	{
		crds[0] = map->pixs[i][j].x_p;
		crds[1] = map->pixs[i][j].y_p;
		crds[2] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].x_p;
		crds[3] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].y_p;
		crds[4] = map->pixs[i][j].col;
		crds[5] = map->pixs[(i + ((fg) ? 1 : 0))][(j + ((fg) ? 0 : 1))].col;
	}
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
**	x0, y0, x1, y1, col0, col1
**	ITER
**	x, y, dir, accretion
**	DATA
**	dx, dy, dxabs, dyabs
*/

void	*bresenham(t_frame *map, int *crds)
{
	int	*data;
	int	*iter;

	if (!(iter = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	if (!(data = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	data[0] = crds[2] - crds[0];
	data[1] = crds[3] - crds[1];
	data[2] = abs(crds[2] - crds[0]);
	data[3] = abs(crds[3] - crds[1]);
	data[4] = ((abs(crds[2] - crds[0]) >= abs(crds[3] - crds[1])) ? 1 : 0);
	iter[0] = crds[0];
	iter[1] = crds[1];
	iter[2] = diff_direction(data[1]);
	iter[3] = diff_direction(data[0]);
	iter[4] = 0;
	// if (abs(crds[2] - crds[0]) >= abs(crds[3] - crds[1]))
	// 	bresenham_dx(map, crds, iter, data);
	// else
	// 	bresenham_dy(map, crds, iter, data);
	bresenham_dx_dy(map, crds, iter, data);
	// br_common_algo(map, crds, iter, data);
	free(crds);
	free(iter);
	free(data);
	return (map);
}

void	put_pix_on_pic(t_frame *map, int x, int y, int col)
{
	int	index;

	if (x < 1000 && x > 0 && y > 0 && y < 1000)
	{
		index = (x << 2) + (y << 2) * 1000;
		map->data->im_data[index] = col;
		map->data->im_data[index + 1] = col >> 8;
		map->data->im_data[index + 2] = col >> 16;
	}
}

/*
**	CRDS
**	x0, y0, x1, y1, col0, col1
**	ITER
**	x, y, dir, accretion, z
**	DATA
**	dx, dy, dxabs, dyabs, col
*/

void	br_common_algo(t_frame *map, int *crds, int *iter, int *data)
{
	// int		sign_x;
	// int		sign_y;
	// int		error[2];

	// // temp.x_p = ft_abs(crds[2] - crds[0]);
	// // temp.y_p = ft_abs(crds[3] - crds[1]);
	// sign_x = ((data[0] > 0) ? 1 : -1);
	// sign_y = ((data[1] > 0) ? 1 : -1);
	// error[0] = data[0] - data[1];
	// // temp.x = crds[0];
	// // temp.y = crds[1];
	// while (iter[0] != crds[2] || iter[1] != crds[3])
	// {
	// 	// put_pixel(map, iter[0], iter[1], get_color(crds, iter, data));
	// 	int col = get_color(crds, iter, data);
	// 	mlx_pixel_put(map->data->mlx, map->data->win, iter[0], iter[1], col);
	// 	if ((error[1] = error[0] * 2) > -data[3])
	// 	{
	// 		error[0] -= data[3];
	// 		iter[0] += sign_x;
	// 	}
	// 	if (error[1] < data[2])
	// 	{
	// 		error[0] += data[2];
	// 		iter[1] += sign_y;
	// 	}
	// }

	t_pix	delta;
	t_pix	sign;
	t_pix	cur;
	int		error[2];

	delta.x = abs(crds[2] - crds[0]);
	delta.y = abs(crds[3] - crds[1]);
	sign.x = crds[0] < crds[2] ? 1 : -1;
	sign.y = crds[1] < crds[3] ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur.x = crds[0];
	cur.y = crds[1];
	while (cur.x != crds[2] || cur.y != crds[3])
	{
		int col = get_color(crds, iter, data);
		// put_pixel(f, cur.x, cur.y, get_color(cur, f, s, delta));
		mlx_pixel_put(map->data->mlx, map->data->win, cur.x, cur.y, col);

		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

/*
**	CRDS
**	x0, y0, x1, y1, col0, col1
**	ITER
**	x, y, sign_x, sign_y, accretion, z
**	DATA
**	dx, dy, dxabs, dyabs, col
*/

void	bresenham_dx(t_frame *map, int *crds, int *iter, int *data)
{
	int col;

	while (iter[0] != crds[2])
	{
		col = get_color(crds, iter, data);
		put_pix_on_pic(map, iter[0], iter[1], col);
		iter[4] += data[3];
		if (iter[4] > data[2])
		{
			iter[4] -= data[2];
			iter[1] += iter[2];
		}
		iter[0] += iter[3];
	}
}

void	bresenham_dy(t_frame *map, int *crds, int *iter, int *data)
{
	int col;

	while (iter[1] != crds[3])
	{
		col = get_color(crds, iter, data);
		put_pix_on_pic(map, iter[0], iter[1], col);
		iter[4] += data[2];
		if (iter[4] > data[3])
		{
			iter[4] -= data[3];
			iter[0] += iter[3];
		}
		iter[1] += iter[2];
	}
}

void	bresenham_dx_dy(t_frame *map, int *crds, int *iter, int *data)
{
	int col;

	while (((data[4]) ? (iter[0] != crds[2]) : (iter[1] != crds[3])))
	{
		col = get_color(crds, iter, data);
		put_pix_on_pic(map, iter[0], iter[1], col);
		iter[4] = iter[4] + ((data[4]) ? data[3] : data[2]);
		if (((data[4]) ? iter[4] > data[2] : iter[4] > data[3]))
		{
			iter[4] = iter[4] - ((data[4]) ? data[2] : data[3]);
			if (data[4])
				iter[1] += iter[2];
			else
				iter[0] += iter[3];
		}
		if (data[4])
			iter[0] += iter[3];
		else
			iter[1] += iter[2];
	}
}
