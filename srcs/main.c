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
	return (0);
}