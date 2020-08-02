/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:41 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 13:37:10 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

typedef struct
{
	void		*mlx;
	void		*win;
	int			wh;
	int			ht;
	int			**mxy;
	int			scale;
	int			sh_x;
	int			sh_y;
	int			type_proj:2;
}				t_frame;

typedef	struct
{
	int			x;
	int			y;
	int			col;
}				t_unit;

t_frame	*init_frame(t_frame *ipt);
t_list	*validation(t_frame *map, char *file_name);
void	*parse_list(t_frame *map, t_list *head);
void	*parse_list_init(t_frame *map, t_list *head, t_list **temp);
void	print_frame(t_frame *map);
int		ft_max(int a, int b);
int		ft_mod(int a);

void	*line_draw(t_frame *map, int x, int y, int flag);
int		diff_direction(int diff_var);
void	*bresenham(t_frame *map, int *crds, int col);
void	*bresenham_dx(t_frame *map, int *crds, int *iter, int *data);
void	*bresenham_dy(t_frame *map, int *crds, int *iter, int *data);

void	*draw_map(t_frame *map);
int		*projection(int *crds, int type_proj);
int		*isometric(int *, double);
int		deal_key(int key, t_frame *map);

int		get_color(int *crds, int *iter, int *data, int flag);

#endif