/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:41 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/21 19:56:57 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		diff_direction(int diff_var);
void	*bresenham(frame *map, int *crds, int col);
void	*bresenham_dx(frame *map, int *crds, int *iter, int *data);
void	*bresenham_dy(frame *map, int *crds, int *iter, int *data);

void	draw_map(frame *map);
void	isometric(float *x, float *y, int z);
int		deal_key(int key, frame *map);


#endif