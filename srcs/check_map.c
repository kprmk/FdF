/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:08:04 by mbrogg            #+#    #+#             */
/*   Updated: 2020/08/06 19:07:09 by mbrogg           ###   ########.fr       */
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

void	errors(int argc)
{
	if (argc == 1)
		urgent_exit("There's been no input file\n");
	else if (argc > 2)
		urgent_exit("There've been too many input files\n");
}

void	urgent_exit(char *s)
{
	if (errno == 0)
		ft_putstr_fd(s, 2);
	else
		perror(s);
	exit(1);
}
