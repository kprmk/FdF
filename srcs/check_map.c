/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:08:04 by mbrogg            #+#    #+#             */
/*   Updated: 2020/08/06 17:08:51 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_scale_and_shift(t_frame *map)
{
	if (map->max_z <= 20 && map->ht < 50)
	{
		map->scale = 20;
		map->sh_x = map->wh * map->scale * ((map->wh <= 10) ? 2.5 : 1);
		map->sh_y = map->ht * map->scale * ((map->wh <= 10) ? 2.5 : 1.5);
	}
	else if (map->max_z <= 50)
	{
		map->scale = ((map->wh <= 20) ? 10 : 3);
		map->sh_x = map->wh * map->scale * ((map->wh <= 20) ? 2.5 : 0.7);
		map->sh_y = map->ht * map->scale * ((map->wh <= 20) ? 3 : 1);
	}
	else
	{
		map->scale = 1;
		map->sh_x = map->wh;
		map->sh_y = map->ht / 2;
	}
}

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
