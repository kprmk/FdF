/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/16 21:29:41 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#define W	1000
#define	H	1000

int main(int argc, char **argv)
{
	frame	*map;
	int		c;

	map = NULL;
	c = 0;
	if (!(map = init_frame(map)))
		return (0);
	while (++c < argc)
	{
		validation(map, argv[c]);
		print_frame(map);
	}
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, W, H, "FdF");
	int crds[4] = {(int)(W / 2), (int)(H / 2), 0, 0};
	draw_map(map);
	for (double i = 0; i <= 3.14 * 2; i += (3.14 / 70))
	{
		ft_printf("%f\n", i);
		// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + cos(i) * 500), (int)(H / 2 + sin(i) * 500), (i < 3.14) ? 0x00ffff: 0xffff00);
		crds[2] = (int)(W / 2 + cos(i) * 500);	
		crds[3] = (int)(H / 2 + sin(i) * 500);	
		bresenham(map, crds, (i < 3.14) ? 0x0f0ff0: 0x00ffff);
	}
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 100), (int)(H / 2 + 100),0xffff00);
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 200), (int)(H / 2 + 100),0xffff00);
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 100), (int)(H / 2 + 200),0xffff00);


	mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	return (0);
}