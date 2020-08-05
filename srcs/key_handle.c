/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:11:14 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 00:34:07 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	input_shift_and_scale(int key, t_frame *map)
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
	if (key == 61 && map->sum_scale < 1)
		map->scale = 1.4;
	if (key == 45 && map->sum_scale > -1)
		map->scale = 0.6;
	if (key == 112)
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

/*
**	CHANGES -> SH_X, SH_Y, SCALE
*/

int		deal_key(int key, t_frame *map)
{
	// int	bp;
	// int	sl;
	// int	en;
	int	i;

	i = -1;
	map->sh_x = 0;
	map->sh_y = 0;
	map->sum_scale += (map->scale - 1);
	map->scale = 1;
	if (key == 65307)
	{
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		free(map);
		exit(0);
	}
	input_shift_and_scale(key, map);
	commit_changes_to_map(map, 0);
	mlx_clear_window(map->data->mlx, map->data->win);
	while (++i < 3 + 1000 * 4 * 1000)
		map->data->im_data[i] = 0;
	// mlx_destroy_image(map->data->mlx, map->data->im);
	// if (!(map->data->im = mlx_new_image(map->data->mlx, 1000, 1000)))
		// return (-1);
	// if (!(map->data->im_data = mlx_get_data_addr(map->data->im, &bp, &sl, &en)))
		// return (-1);
	draw_map(map);
	return (0);
}
