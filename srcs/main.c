/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 17:18:47 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#define W 1000
#define H 1000

int main(int argc, char **argv)
{
	t_frame	*map;
	int		c;

	map = NULL;
	c = 0;
	if (!(map = init_frame(map, W, H)))
		return (0);
	while (++c < argc)
	{
		if (!(validation(map, argv[c])))
			return (0);
		print_frame(map);
	}
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, W, H, "FdF");
	draw_map(map);

	mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	free(map);
	ft_printf("asdfhadfjhasdfhasdf");
	return (0);
}

void test_draw()
{
	//	##############TEST###############################
	// for (double i = 0; i <= 3.14 * 2; i += (3.14 / 70))
	// {
	// 	ft_printf("%f\n", i);
	// 	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + cos(i) * 500), (int)(H / 2 + sin(i) * 500), (i < 3.14) ? 0x00ffff: 0xffff00);
	// 	crds[2] = (int)(W / 2 + cos(i) * 500);	
	// 	crds[3] = (int)(H / 2 + sin(i) * 500);	
	// 	bresenham(map, crds, (i < 3.14) ? 0x0f0ff0: 0x00ffff);
	// }
}