/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:58:11 by kprmk             #+#    #+#             */
/*   Updated: 2020/08/05 17:08:36 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_frame	*init_frame(t_frame *ipt)
{
	if (!(ipt = (t_frame *)malloc(sizeof(t_frame))))
		return (NULL);
	ipt->ht = 0;
	ipt->wh = 0;
	ipt->pixs = NULL;
	ipt->scale = 20;
	ipt->sh_x = 0;
	ipt->sh_y = 0;
	ipt->type_proj = 0;
	ipt->angle_iso = 30;
	ipt->rotated_axis = 0;
	ipt->max_z = 0;
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

int		get_color_after_comma(const char *str)
{
	int				i;
	int				power;
	unsigned long	res;

	power = 6;
	i = 0;
	res = 0;
	while (i < ft_strlen(str) && str[i] != ',')
		++i;
	if (str[i + 1] == '0' && str[i + 2] == 'x')
	{
		i += 3;
		while (power)
		{
			if (str[i] >= 'A' && str[i] <= 'F')
				res = res * 16 + str[i] - 'A' + 10;
			else if (str[i] >= '0' && str[i] <= '9')
				res = res * 16 + str[i] - '0';
			else
				break;
			++i;
			--power;
		}
	}
	else
		return (-1);
	return ((int)res);
}

void	get_scale_and_shift(t_frame *map)
{
	ft_printf("MAX_Z %d\n", map->max_z);
	if (map->max_z <= 20 && map->ht < 50)
	{
		map->scale = 20;
		map->sh_x = map->wh * map->scale * ((map->wh <= 10) ? 2.5 : 1); 
		map->sh_y = map->ht * map->scale * ((map->wh <= 10) ? 2.5 : 1.5);
	}
	else if (map->max_z <= 50)
	{
		ft_printf("#######################\n");
		map->scale = 10;
		map->sh_x = map->wh * map->scale * 2.5; 
		map->sh_y = map->ht * map->scale * 3;
	}
	else
	{
		map->scale = 1;
		map->sh_x = map->wh; 
		map->sh_y = map->ht / 2;
	}
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
		{
			double angle = 26.57 * M_PI / 180;
			map->pixs[i][c].z = ft_atoi(strs[c]);
			map->pixs[i][c].x = (c - i) * cos(angle);
			map->pixs[i][c].y = (c + i) * sin(angle) - map->pixs[i][c].z;
			if (map->max_z < map->pixs[i][c].z)
				map->max_z = map->pixs[i][c].z;
			int res = get_color_after_comma(strs[c]);
			if (res != -1)
				map->pixs[i][c].col = res;
			else if (map->pixs[i][c].z)
				map->pixs[i][c].col = 0x00ffff;
			else
				map->pixs[i][c].col = 0xFC7F12; // 0xFC12B6
		}
		strs = ft_free_split(strs, -1);
		temp = temp->prev;
	}
	commit_changes_to_map(map, 1);
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
