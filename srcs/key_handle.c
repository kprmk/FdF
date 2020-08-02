/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:11:14 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 18:07:38 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(int key, t_frame *map)
{
	// int angle;

	// if (map)
	// 	angle = 10 * M_PI / 180;
	if (key == 120 || key == 121 || key == 122)
	{
		map->rotated_angle += 10;
		if (key == 120)
			map->rotated_axis = 1;
		if (key == 121)
			map->rotated_axis = 2;
		if (key == 122)
			map->rotated_axis = 3;
	}
}

void	shift_map(int key, t_frame *map)
{
	int	shift_step;

	shift_step = 20;
	if (key == 65363)
		map->sh_x += shift_step;
	if (key == 65362)
		map->sh_y -= shift_step;
	if (key == 65364)
		map->sh_y += shift_step;
	if (key == 65361)
		map->sh_x -= shift_step;	
}

void scale_and_proj(int key, t_frame *map)
{
	int	dif_scale;

	dif_scale = 3;
	if (key == 61)
		map->scale += dif_scale;
	if (key == 45)
		map->scale -= dif_scale;
	if (key == 112)
		map->type_proj = (map->type_proj + 1) % 3;
	if (key == 97)
		map->angle_iso++;
	if (key == 115)
		map->angle_iso--;
}

int		deal_key(int key, t_frame *map)
{
	ft_printf("%d\n", key);
	if (key == 65307)
	{
		free(map);
		exit(0);
	}	
	shift_map(key, map);
	scale_and_proj(key, map);
	rotate(key, map);
	mlx_clear_window(map->mlx, map->win);
	draw_map(map);
	return (0);
}