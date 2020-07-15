#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <mlx.h>
#include <math.h>

typedef struct
{
	void    *mlx;
	void    *win;
	int		wh;
	int		ht;
	int		**mxy;
	int		scale;
	int		sh_x;
	int		sh_y;
}			frame;

frame	*init_frame(frame *ipt);
t_list	*validation(frame *map, char *file_name);
void	*parse_list(frame *map, t_list *head);
void	*parse_list_init(frame *map, t_list *head, t_list **temp);
void	print_frame(frame *map);
int		ft_max(int a, int b);
int		ft_mod(int a);
void	draw_line(frame *map, float x1, float y1, float x2, float y2);
void	bresenham(frame *map, int x1, int y1, int x2, int y2, int col);
void	draw_map(frame *map);
void	isometric(float *x, float *y, int z);
int		deal_key(int key, frame *map);
int		diff_direction(int diff_var);
void	brezenham_draw(frame *map, int x1, int y1, int x2, int y2, int col);
void	bresenham_2(frame *map, int x1, int y1, int x2, int y2, int col);


#endif