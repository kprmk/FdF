#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <mlx.h>

typedef struct
{
    int wh;
    int ht;
    int **mtx;
}       frame;

frame	*init_frame(frame *ipt);
t_list	*validation(frame *map, char *file_name);
void	*parse_list(frame *map, t_list *head);
void	*get_height_from_list(frame *map, t_list *head, t_list **temp);
void	print_frame(frame *map);



#endif