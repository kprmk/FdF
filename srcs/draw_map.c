#include "fdf.h"

int		deal_key(int key, frame *map)
{
	ft_printf("%d\n", key);
	if (key == 65293)
		map->sh_y -= 1;
	if (key == 65362)
		map->sh_y += 1;
	if (key == 65364)
		map->sh_x += 1;
	if (key == 65361)
		map->sh_x -= 1;
	draw_map(map);
	return (0);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	*draw_map(frame *map)
{
	int	i; 
	int	j;
	int	*crds;

	i = 0;
	if (!(crds = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	while (i < map->ht)
	{
		j = 0;
		while (j < map->wh)
		{
			crds[0] = j * map->scale;
			crds[1] = i * map->scale;
			if (j < map->wh - 1)
			{
				crds[2] = (j + 1) * map->scale;
				crds[3] = i * map->scale;
				if (!line_draw(map, crds, 1))
					return (NULL);
			}
			if (i < map->ht - 1)
			{
				crds[2] = j * map->scale;
				crds[3] = (i + 1) * map->scale;
				if (!line_draw(map, crds, 0))
					return (NULL);
			}
			++j;
		}
		++i;
	}
	free(crds);
	return (NULL);
}