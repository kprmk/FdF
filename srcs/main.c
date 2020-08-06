/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 17:26:34 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_frame	*map;

	map = NULL;
	if (!(errors(argc)) || !(map = init_frame(map)))
		return (0);
	if (!(validation(map, argv[1])))
		return (0);
	if (!(init_data_mlx(map, W, H)))
		return (0);
	draw_map(map);
	mlx_key_hook(map->data->win, deal_key, map);
	mlx_loop(map->data->mlx);
	free_map(&map);
	return (0);
}
