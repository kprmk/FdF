#include "fdf.h"

#include <math.h>
#define W	1000
#define	H	1000

int main(int argc, char **argv)
{
	frame	*map;
	int		c;

	map = NULL;
	c = 0;
	if (!(map = init_frame(map)))
		return (0);
	while (++c < argc)
	{
		validation(map, argv[c]);
		print_frame(map);
	}
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, W, H, "FdF");
	draw_map(map);
	for (double i = 0; i <= 3.14 * 2; i += (3.14 / 24))
	{
		ft_printf("%f\n", i);
		bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + cos(i) * 300), (int)(H / 2 + sin(i) * 300), (i < 3.14) ? 0x00ffff: 0xffff00);
	}
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 100), (int)(H / 2 + 100),0xffff00);
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 200), (int)(H / 2 + 100),0xffff00);
	// bresenham(map, (int)(W / 2), (int)(H / 2), (int)(W / 2 + 100), (int)(H / 2 + 200),0xffff00);


	mlx_key_hook(map->win, deal_key, map);
	mlx_loop(map->mlx);
	return (0);
}