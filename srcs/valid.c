/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:58:11 by kprmk             #+#    #+#             */
/*   Updated: 2020/07/21 20:40:51 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

frame	*init_frame(frame *ipt)
{
	if (!(ipt = (frame *)malloc(sizeof(frame))))
		return (NULL);
	ipt->ht = 0;
	ipt->wh = 0;
	ipt->mxy = NULL;
	ipt->scale = 50;
	ipt->sh_x = 0;
	ipt->sh_y = 0;
	return (ipt);
}

t_list	*validation(frame *map, char *file_name)
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
	}
	if (!(parse_list(map, head)))
		return (NULL);
	return (head);
}

void	*parse_list(frame *map, t_list *head)
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
			map->mxy[i][c] = ft_atoi(strs[c]);
		strs = ft_free_split(strs, -1);
		temp = temp->prev;
	}
	return (map);
}

void	*parse_list_init(frame *map, t_list *head, t_list **temp)
{
	*temp = head;
	while ((*temp)->next)
		*temp = (*temp)->next;
	if (!(map->mxy = (int **)malloc(sizeof(int *) * map->ht)))
		return (NULL);
	return (*temp);
}

void	print_frame(frame *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < map->ht)
	{
		j = -1;
		while (++j < map->wh)
			ft_printf("%2d ", map->mxy[i][j]);
		ft_printf("\n");
	}
}
