#include "fdf.h"

int main(int argc, char **argv)
{
	frame	*map;
	int		c;

	map = NULL;
	c = 0;
	while (++c < argc)
	{
 		map = init_frame(map);
		validation(map, argv[c]);
		print_frame(map);
	}
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1000, 1000, "FdF");
	/**/
	map->scale = 50;
	/**/
	draw_map(map);
	mlx_loop(map->mlx);
	return (0);
}