/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:40 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 15:35:38 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			ft_printf("%d %X, ", (int)map->pixs[i][j].z, map->pixs[i][j].col);
		ft_printf("\n");
	}
}

int		errors(int argc)
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
