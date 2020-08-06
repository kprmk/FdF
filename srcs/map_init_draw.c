/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 19:01:27 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_frame	*init_frame(t_frame *map)
{
	if (!(map = (t_frame *)malloc(sizeof(t_frame))))
		urgent_exit("There\'s been mem alloc fail\n");
	map->scale = 20;
	map->sh_x = 0;
	map->sh_y = 0;
	map->ht = 0;
	map->wh = 0;
	map->type_proj = 0;
	map->angle_iso = 30;
	map->max_z = 0;
	return (map);
}

/*
**	bp - number of bits per pixels (4 * 8)
**	sl - size line (len(ar_ins))
**	en - endian -> "Endianness" (big-endian / small-endian) ARCH
*/

void	init_data_mlx(t_frame *map, int w, int h)
{
	int	bp;
	int	sl;
	int	en;

	if (!(map->data = (t_mlx *)malloc(sizeof(t_mlx))))
		urgent_exit("There\'s been mem alloc fail\n");
	if (!(map->data->mlx = mlx_init()))
		urgent_exit("There\'s been mem alloc fail\n");
	if (!(map->data->win = mlx_new_window(map->data->mlx, w, h, "MBROGG")))
		urgent_exit("There\'s been mem alloc fail\n");
	if (!(map->data->im = mlx_new_image(map->data->mlx, w, h)))
		urgent_exit("There\'s been mem alloc fail\n");
	if (!(map->data->i_data = mlx_get_data_addr(map->data->im, &bp, &sl, &en)))
		urgent_exit("There\'s been mem alloc fail\n");
}

void	free_map(t_frame **map)
{
	int	i;

	i = -1;
	while (++i < (*map)->ht)
		free((*map)->pixs[i]);
	free((*map)->pixs);
	free((*map)->data->mlx);
	free((*map)->data->win);
	free((*map)->data->im);
	free((*map)->data);
	free(*map);
	*map = NULL;
}

void	draw_map(t_frame *map)
{
	int		i;
	int		j;
	void	*temp;

	i = 0;
	while (i < map->ht)
	{
		j = 0;
		while (j < map->wh)
		{
			if (j < map->wh - 1)
				line_draw(map, j, i, 0);
			if (i < map->ht - 1)
				line_draw(map, j, i, 1);
			++j;
		}
		++i;
	}
	temp = map->data->mlx;
	mlx_put_image_to_window(temp, map->data->win, map->data->im, 0, 0);
}
