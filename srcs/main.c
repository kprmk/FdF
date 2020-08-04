/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/04 14:49:11 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#define W 1000
#define H 1000

void	print_frame(t_frame *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < map->ht)
	{
		j = -1;
		while (++j < map->wh)
		{
			if (map->pixs[i][j].col == 0xffffff)
				ft_printf("%2d ", map->pixs[i][j].z);
			else
				ft_printf("%2d,%X ", map->pixs[i][j].z, map->pixs[i][j].col);
		}
		ft_printf("\n");
	}
}

int	errors(int argc)
{
	if (argc == 1)
	{
		ft_printf("There's been no input file\n");
		return (0);
	}
	else if (argc > 2)
	{
		ft_printf("There've been too many input files\n");
		return (0);
	}
	else
		return (1);
}


int	main(int argc, char **argv)
{
	t_frame	*map;

	map = NULL;
	if (!(errors(argc)) || !(map = init_frame(map)))
		return (0);
	if (!(validation(map, argv[1])))
		return (0);
	// print_frame(map);
	ft_printf("SIZES %d %d", map->ht, map->wh);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, W, H, "MBROGG");
	draw_map(map);
	mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	// FREEEE PIXS!!!!!!!!!!!!!!!!!!!!!!!
	free(map);

	// #include <stdio.h>
	// char str[] = "155,0xFE950C";
	// if (argc || argv)
	// 	printf("%d %X\n", get_color_after_comma(str), get_color_after_comma(str));
	
	
	// int color = 0x6A317C;
	// printf("%X\n", color);

	// int red = (color >> 16) & 0xff;
	// int green = (color >> 8) & 0xff;
	// int blue = color & 0x0000ff;
	// if (argc || argv)
	// 	ft_printf("%X -> \nr %d, g %d, b %d\n%X, %X, %X\n", color, red, green, blue, red, green, blue);
	// int res = red << 16 | green << 8 | blue;
	// ft_printf("res -> %d\t%X", res, res);
	return (0);
}
