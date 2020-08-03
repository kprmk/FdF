/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:11:14 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 23:52:56 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_map(int key, t_frame *map)
{
	int	shift_step;

	shift_step = 20;
	if (key == 124)
		map->sh_x += shift_step;
	if (key == 126)
		map->sh_y -= shift_step;
	if (key == 125)
		map->sh_y += shift_step;
	if (key == 123)
		map->sh_x -= shift_step;
}

void	scale_and_proj(int key, t_frame *map)
{
	int	dif_scale;

	dif_scale = 3;
	if (key == 24)
		map->scale += dif_scale;
	if (key == 27)
		map->scale -= dif_scale;
	if (key == 35)
		map->type_proj = (map->type_proj + 1) % 4;
	if (key == 0)
		map->angle_iso++;
	if (key == 1)
		map->angle_iso--;
}

int		deal_key(int key, t_frame *map)
{
	if (key == 53)
	{
		free(map);
		exit(0);
	}
	shift_map(key, map);
	scale_and_proj(key, map);
	mlx_clear_window(map->mlx, map->win);
	draw_map(map);
	return (0);
}
