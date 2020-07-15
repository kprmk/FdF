#include "fdf.h"

/*
**	draw_line
**	ss - steps
*/

void	draw_line(frame *map, float x1, float y1, float x2, float y2)
{
	float	x_ss;
	float	y_ss;
	int		max;

	int color = map->mxy[(int)y1][(int)x1] ? 0xffff00: 0x00ffff;

	// isometric(&x1, &y1, map->mxy[(int)y1][(int)x1]);
	// isometric(&x2, &y2, map->mxy[(int)y2][(int)x2]);

	// x1 += map->sh_x;
	// y1 += map->sh_y;
	// x2 += map->sh_x;
	// y1 += map->sh_y;

	x1 *= map->scale;
	y1 *= map->scale;
	x2 *= map->scale;
	y2 *= map->scale;
	x_ss = x2 - x1;
	y_ss = y2 - y1;
	max = ft_max(ft_mod(x_ss), ft_mod(y_ss));
	x_ss /= max;
	y_ss /= max;
	while ((int)(x2 - x1) || (int)(y2 - y1))
	{
		mlx_pixel_put(map->mlx, map->win, x1, y1, color);
		x1 += x_ss;
		y1 += y_ss;
	}
}

int	diff_direction(int diff_var)
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
*/

void	bresenham(frame *map, int x1, int y1, int x2, int y2, int col)
{
	int	d;
	int	d1;
	int	d2;
	int	dif;
	int dx;
	int	dy;
	int x;
	int	y;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;

	if (abs(dx) >= abs(dy))
	{
		d = dx * 2 - dy;
		d1 = dy * 2;
		d2 = (dy - dx) * 2;
		ft_printf("~~~~~~\n");
		dif = diff_direction(dy);
		while ((dx > 0) ? x <= x2: x >= x2)
		{
			mlx_pixel_put(map->mlx, map->win, x, y, col);
			if (d < 0)
				d += d1;
			else
			{
				y += dif;
				d += d2;
			}
			x = (dx > 0) ? x + 1: x - 1;
		}
	}
	else
	{
		d = dy * 2 - dx;
		d1 = dx * 2;
		d2 = (dx - dy) * 2;
		ft_printf("!!!!!!!!\n");
		dif = diff_direction(dx);
		while ((dy > 0) ? y <= y2: y >= y2)
		{
			mlx_pixel_put(map->mlx, map->win, x, y, col);
			if (d < 0)
				d += d1;
			else
			{
				x += dif;
				d += d2;
			}
			y = (dy > 0) ? y + 1: y - 1;
		}
	}

	// if (dxabs >= dyabs)
	// {
	// 	dir = diff_direction(dy);
	// 	while ((dx > 0) ? x1 <= x2: x1 >= x2)
	// 	{
	// 		mlx_pixel_put(map->mlx, map->win, x1, y1, col);
	// 		accretion += dyabs;

	// 		if (accretion > dxabs)
	// 		{
	// 			accretion -= dxabs;
	// 			y1 += dir;
	// 		}

	// 		x1 = (dx > 0) ? x1 + 1: x1 - 1;
	// 	}
	// }
	// else
	// {
	// 	dir = diff_direction(dx);
	// 	while ((dy > 0) ? y1 <= y2: y1 >= y2)
	// 	{
	// 		mlx_pixel_put(map->mlx, map->win, x1, y1, col);
	// 		accretion += dxabs;
	// 		if (accretion > dyabs)
	// 		{
	// 			accretion -= dyabs;
	// 			x1 += dir;
	// 		}

	// 		y1 = (dy > 0) ? y1 + 1: y1 - 1;
	// 	}
	// }
}

// void	brezenham_draw(frame *map, int xi, int yi, int xd, int yd, int col)
// {
	// int	dir;
	// int	accretion;
	// int	d_i;
	// int	d_i_abs;
	// int	d_d;
	// int	d_d_abs;

	// dir = diff_direction(xi);
	// while ((dx > 0) ? x1 <= x2: x1 >= x2)
	// {
	// 	mlx_pixel_put(map->mlx, map->win, x1, y1, col);
	// 	accretion += dyabs;

	// 	if (accretion > dxabs)
	// 	{
	// 		accretion -= dxabs;
	// 		y1 += dir;
	// 	}

	// 	x1 = (dx > 0) ? x1 + 1: x1 - 1;
	// }
// }

