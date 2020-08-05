/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:41 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 16:49:05 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

typedef	struct	s_pix
{
	float			x;
	float			y;
	int			z;
	int			col;
}				t_pix;

typedef struct	s_frame
{
	void		*mlx;
	void		*win;
	int			wh;
	int			ht;
	t_pix		**pixs;
	float		scale;
	int			sh_x;
	int			sh_y;
	int			type_proj;
	int			angle_iso;
	int			rotated_axis : 3;
	int			rotated_angle;
	int			max_z;
}				t_frame;


t_frame			*init_frame(t_frame *ipt);
void			*validation(t_frame *map, char *file_name);
void			*parse_list(t_frame *map, t_list *head);
void			*parse_list_init(t_frame *map, t_list *head, t_list **temp);
void			print_frame(t_frame *map);
int				ft_max(int a, int b);
int				ft_mod(int a);

void			*line_draw(t_frame *map, int x, int y, int flag);
int				diff_direction(int diff_var);
void			*bresenham(t_frame *map, int *crds);
void			bresenham_dx(t_frame *map, int *crds, int *iter, int *data);
void			bresenham_dy(t_frame *map, int *crds, int *iter, int *data);

void			*draw_map(t_frame *map);
int				*projection(int *crds, t_frame *map);

int				deal_key(int key, t_frame *map);
int				get_color(int *crds, int *iter, int *data);

void			commit_changes_to_map(t_frame *map, int flag);

#endif
