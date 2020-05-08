#include "fdf.h"

void	draw_map(frame *map)
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
				draw_line(map, j, i, j + 1, i);
			if (i < map->ht - 1)			
				draw_line(map, j, i, j, i + 1);
			++j;	
		}
		++i;
	}
}