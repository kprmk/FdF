/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:50:25 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 20:59:08 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_frame	*init_frame(t_frame *ipt)
{
	if (!(ipt = (t_frame *)malloc(sizeof(t_frame))))
		return (NULL);
	ipt->ht = 0;
	ipt->wh = 0;
	ipt->pixs = NULL;
	ipt->scale = 20;
	ipt->sh_x = 0;
	ipt->sh_y = 0;
	ipt->type_proj = 0;
	ipt->angle_iso = 30;
	ipt->max_z = 0;
	return (ipt);
}

void	free_map(t_frame **map)
{
	int	i;

	i = -1;
	while (++i)
		free((*map)->pixs[i]);
	free((*map)->pixs);
	free(*map);
	*map = NULL;
}

void	*draw_map(t_frame *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->ht)
	{
		j = 0;
		while (j < map->wh)
		{
			if (j < map->wh - 1)
				if (!line_draw(map, j, i, 0))
					return (NULL);
			if (i < map->ht - 1)
				if (!line_draw(map, j, i, 1))
					return (NULL);
			++j;
		}
		++i;
	}
	return (NULL);
}
