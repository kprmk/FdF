/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:58:11 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/02 23:27:19 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_frame	*init_frame(t_frame *ipt, int width, int height)
{
	if (!(ipt = (t_frame *)malloc(sizeof(t_frame))))
		return (NULL);
	ipt->ht = 0;
	ipt->wh = 0;
	ipt->mxy = NULL;
	ipt->scale = 20;
	ipt->sh_x = width / 4;
	ipt->sh_y = height / 4;
	ipt->type_proj = 0;
	ipt->angle_iso = 30;
	ipt->rotated_axis = 0;
	return (ipt);
}

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
		if (!(map->mxy[++i] = (int *)malloc(sizeof(int) * map->wh)))
			return (NULL);
		while (strs[++c])
			map->mxy[i][c] = ft_atoi(strs[c]) * 10;
		strs = ft_free_split(strs, -1);
		temp = temp->prev;
	}
	return (map);
}

void	*parse_list_init(t_frame *map, t_list *head, t_list **temp)
{
	*temp = head;
	while ((*temp)->next)
		*temp = (*temp)->next;
	if (!(map->mxy = (int **)malloc(sizeof(int *) * map->ht)))
		return (NULL);
	return (*temp);
}
