/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:11:14 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 17:26:30 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	input_shift(int key, t_frame *map)
{
	int shift;

	shift = 30;
	if (map->type_proj == 0)
	{
		if (key == 124 && map->pixs[0][map->wh - 1].x < W)
			map->sh_x = shift;
		if (key == 126 && map->pixs[0][0].y > 0)
			map->sh_y = -shift;
		if (key == 125 && map->pixs[map->ht - 1][map->wh - 1].y < H)
			map->sh_y = shift;
		if (key == 123 && map->pixs[map->ht - 1][0].x > 0)
			map->sh_x = -shift;
	}
	else
	{
		if (key == 124 && map->pixs[0][map->wh - 1].x_p < W)
			map->sh_x = shift;
		if (key == 126 && map->pixs[0][0].y_p > 0)
			map->sh_y = -shift;
		if (key == 125 && map->pixs[map->ht - 1][map->wh - 1].y_p < H)
			map->sh_y = shift;
		if (key == 123 && map->pixs[map->ht - 1][0].x_p > 0)
			map->sh_x = -shift;
	}
}

void	input_shift_and_scale(int key, t_frame *map)
{
	input_shift(key, map);
	if (map->type_proj == 0)
	{
		if (key == 24 && (mod(map->pixs[0][0].x - map->pixs[0][1].x) < 50))
			map->scale = 1.4;
		if (key == 27 && (mod(map->pixs[0][0].x - map->pixs[0][1].x) > 10))
			map->scale = 0.6;
	}
	else
	{
		if (key == 24 && (mod(map->pixs[0][0].x_p - map->pixs[0][1].x_p) < 50))
			map->scale = 1.4;
		if (key == 27 && (mod(map->pixs[0][0].x_p - map->pixs[0][1].x_p) > 10))
			map->scale = 0.6;
	}
	if (key == 35)
		map->type_proj = ((map->type_proj == 1) ? 0 : 1);
	if (key == 97)
		map->angle_iso++;
	if (key == 115)
		map->angle_iso--;
}

void	commit_changes_to_map_body(t_frame *map, int flag, int i, int j)
{
	if (map->type_proj == 0)
	{
		map->pixs[i][j].x = map->pixs[i][j].x * map->scale + map->sh_x;
		map->pixs[i][j].y = map->pixs[i][j].y * map->scale + map->sh_y;
	}
	if (map->type_proj != 0 || flag != 0)
	{
		map->pixs[i][j].x_p = map->pixs[i][j].x_p * map->scale + map->sh_x;
		map->pixs[i][j].y_p = map->pixs[i][j].y_p * map->scale + map->sh_y;
	}
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
				commit_changes_to_map_body(map, flag, i, j);
		}
	}
	if (flag != 0)
		map->scale = 1;
}

int		deal_key(int key, t_frame *map)
{
	map->sh_x = 0;
	map->sh_y = 0;
	map->sum_scale += (map->scale - 1);
	map->scale = 1;
	if (key == 53)
	{
		free_map(&map);
		exit(0);
	}
	input_shift_and_scale(key, map);
	commit_changes_to_map(map, 0);
	ft_bzero(map->data->i_data, 3 + W * 4 * W);
	draw_map(map);
	return (0);
}
