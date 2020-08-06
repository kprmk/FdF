/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 19:03:34 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_frame	*map;

	map = NULL;
	errno = 0;
	errors(argc);
	if (!(map = init_frame(map)))
		urgent_exit("There\'s been mem alloc fail\n");
	validation(map, argv[1]);
	init_data_mlx(map, W, H);
	draw_map(map);
	mlx_key_hook(map->data->win, deal_key, map);
	mlx_loop(map->data->mlx);
	free_map(&map);
	return (0);
}
