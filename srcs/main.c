/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/03 13:18:24 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#define W 1000
#define H 1000

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
	if (!(errors(argc)) || !(map = init_frame(map, W, H)))
		return (0);
	if (!(validation(map, argv[1])))
		return (0);
	print_frame(map);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, W, H, "MBROGG");
	draw_map(map);
	mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	free(map);
	return (0);
}
