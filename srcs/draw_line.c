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

	isometric(&x1, &y1, map->mxy[(int)y1][(int)x1]);
	isometric(&x2, &y2, map->mxy[(int)y2][(int)x2]);

	x1 += map->sh_x;
	y1 += map->sh_y;
	x2 += map->sh_x;
	y1 += map->sh_y;

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

void	bresenham(frame *map, int x1, int y1, int x2, int y2) 
{ 
	int m_new = 2 * (y2 - y1); 
	int slope_error_new = m_new - (x2 - x1); 
	for (int x = x1, y = y1; x <= x2; x++) 
	{
		mlx_pixel_put(map->mlx, map->win, x, y, 0x00FFFF);
		// ft_printf("%d <-> %d\n", x, x);
		slope_error_new += m_new; 
		if (slope_error_new >= 0) 
		{ 
			y++; 
			slope_error_new  -= 2 * (x2 - x1); 
		} 
	}
} 

