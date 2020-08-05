/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:11:14 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 19:29:12 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_map(int key, t_frame *map)
{
	int shift;

	shift = 30;
	if (key == 65363)
		map->sh_x = shift;
	if (key == 65362)
		map->sh_y = -shift;
	if (key == 65364)
		map->sh_y = shift;
	if (key == 65361)
		map->sh_x = -shift;
}

void	scale_and_proj(int key, t_frame *map)
{
	if (key == 61 && map->sum_scale < 1)
		map->scale = 1.4;
	if (key == 45 && map->sum_scale > -1)
		map->scale = 0.6;
	if (key == 112)
		map->type_proj = (map->type_proj + 1) % 3;
	if (key == 97)
		map->angle_iso++;
	if (key == 115)
		map->angle_iso--;
}

void	commit_changes_to_map(t_frame *map, int flag)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (flag != 0)
		get_scale_and_shift(map);
	if (map->sh_x || map->sh_y || map->scale != 1)
	{
		while (++i < map->ht)
		{
			j = -1;
			while (++j < map->wh)
			{
				map->pixs[i][j].x = map->pixs[i][j].x * map->scale + map->sh_x;
				map->pixs[i][j].y = map->pixs[i][j].y * map->scale + map->sh_y;
			}
		}
	}
	if (flag != 0)
		map->scale = 1;
}

/*
**	CHANGES -> SH_X, SH_Y, SCALE
*/

int		deal_key(int key, t_frame *map)
{
	map->sh_x = 0;
	map->sh_y = 0;
	map->sum_scale += (map->scale - 1);
	map->scale = 1;
	ft_printf("SUM_SCALE -> %f\n", map->sum_scale);
	if (key == 65307)
	{
		free(map);
		exit(0);
	}
	shift_map(key, map);
	scale_and_proj(key, map);
	commit_changes_to_map(map, 0);
	mlx_clear_window(map->mlx, map->win);
	draw_map(map);
	return (0);
}
