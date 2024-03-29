/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:41 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 19:06:37 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>

# define W 1000
# define H 1000

typedef	struct	s_pix
{
	float		x;
	float		y;
	float		z;
	int			x_p;
	int			y_p;
	int			col;
}				t_pix;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*im;
	char		*i_data;
}				t_mlx;

typedef struct	s_frame
{
	t_mlx		*data;
	t_pix		**pixs;
	int			wh;
	int			ht;
	float		scale;
	float		sh_x;
	float		sh_y;
	int			type_proj;
	int			angle_iso;
	float		sum_scale;
	int			max_z;
	int			min_y;
}				t_frame;

t_frame			*init_frame(t_frame *map);
void			init_data_mlx(t_frame *map, int w, int h);
void			validation(t_frame *map, char *file_name);
void			parse_list(t_frame *map, t_list *head);
int				get_color_after_comma(const char *str);
void			get_scale_and_shift(t_frame *map);
void			print_frame(t_frame *map);
void			errors(int argc);

void			line_draw(t_frame *map, int x, int y, int flag);
int				diff_direction(int diff_var);
void			bresenham(t_frame *map, int *crds);
void			bresenham_dx_dy(t_frame *map, int *crds, int *iter, int *data);
void			bresenham_dx(t_frame *map, int *crds, int *iter, int *data);
void			bresenham_dy(t_frame *map, int *crds, int *iter, int *data);

void			draw_map(t_frame *map);
int				deal_key(int key, t_frame *map);
int				get_color(int *crds, int *iter, int *data);

void			commit_changes_to_map(t_frame *map, int flag);
void			free_map(t_frame **map);
void			urgent_exit(char *s);

#endif
