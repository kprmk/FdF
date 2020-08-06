/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrogg <mbrogg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:58:11 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/06 18:08:50 by mbrogg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	del_func(void *to_del, size_t size)
{
	if (size)
		free(to_del);
}

void	*validation(t_frame *map, char *file_name)
{
	int		fd;
	char	*str;
	t_list	*head;

	head = NULL;
	fd = open(file_name, O_RDONLY, 0);
	if (fd > 0)
	{
		while (get_next_line(fd, &str))
		{
			map->ht++;
			ft_lstadd(&head, ft_lstnew(str, sizeof(str)));
			free(str);
		}
		free(str);
	}
	else
		return (NULL);
	if (!(parse_list(map, head)))
		return (NULL);
	ft_lstdel(&head, del_func);
	close(fd);
	return (map);
}

void	*parse_list_init(t_frame *map, t_list *head, t_list **temp)
{
	*temp = head;
	while ((*temp)->next)
		*temp = (*temp)->next;
	if (!(map->pixs = (t_pix **)malloc(sizeof(t_pix *) * map->ht)))
		return (NULL);
	return (*temp);
}

/*
**	ISO
**
**	Orthographic Projection
**
**	The most common axonometric projection is an isometric
**	projection where the projection plane intersects each coordinate
**	axis in the model coordinate system at an equal distance.
**
**	CRDS
**	x0, y0, x1, y1, z0, z1
*/

void	parse_list_body(t_frame *map, int i, int c, char **strs)
{
	int		res;

	map->pixs[i][c].x_p = c;
	map->pixs[i][c].y_p = i;
	map->pixs[i][c].z = ft_atoi(strs[c]);
	map->pixs[i][c].x = (c - i) * cos(26.57 * M_PI / 180);
	map->pixs[i][c].y = (c + i) * sin(26.57 * M_PI / 180) - map->pixs[i][c].z;
	if (map->max_z < map->pixs[i][c].z)
		map->max_z = map->pixs[i][c].z;
	res = get_color_after_comma(strs[c]);
	if (res != -1)
		map->pixs[i][c].col = res;
	else if (map->pixs[i][c].z == 0)
		map->pixs[i][c].col = 0xFC7F12;
	else if (map->pixs[i][c].z < 0)
		map->pixs[i][c].col = 0xDE5C1B;
	else if (map->pixs[i][c].z <= 10)
		map->pixs[i][c].col = 0x00cccc;
	else if (map->pixs[i][c].z < 20)
		map->pixs[i][c].col = 0xFC12B6;
	else if (map->pixs[i][c].z > 20)
		map->pixs[i][c].col = 0xff0ff0;
	else
		map->pixs[i][c].col = 0xffffff;
}

void	*parse_list(t_frame *map, t_list *head)
{
	t_list	*temp;
	char	**strs;
	int		i;
	int		c;

	i = -1;
	if (!(parse_list_init(map, head, &temp)))
		return (NULL);
	while (temp)
	{
		c = -1;
		strs = ft_strsplit(temp->content, ' ');
		if (!map->wh)
			while (strs[map->wh])
				map->wh++;
		if (!(map->pixs[++i] = (t_pix *)malloc(sizeof(t_pix) * map->wh)))
			return (NULL);
		while (strs[++c])
			parse_list_body(map, i, c, strs);
		strs = ft_free_split(strs, -1);
		temp = temp->prev;
	}
	commit_changes_to_map(map, 1);
	ft_printf("zmax %d ymin %d\n", map->max_z, map->min_y);
	return (map);
}
