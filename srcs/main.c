#include "fdf.h"

int main(int argc, char **argv)
{
	frame	*map;
	int		c;

	map = NULL;
	c = 0;
	while (++c < argc)
	{
 		if (!(map = init_frame(map)))
		 	return (0);
		validation(map, argv[c]);
		print_frame(map);
	}
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1000, 1000, "FdF");
	draw_map(map);
	// mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	return (0);
}