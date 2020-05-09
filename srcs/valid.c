#include "fdf.h"

frame	*init_frame(frame *ipt)
{
	if (!(ipt = (frame *)malloc(sizeof(frame))))
		return (NULL);
	ipt->ht = 0;
	ipt->wh = 0;
	ipt->mx = NULL;
	ipt->scale = 50;
	ipt->sh_x = 0;
	ipt->sh_y = 0;
	return (ipt);
}

/*
**	
*/

t_list	*validation(frame *map, char *file_name)
{
	int     fd;
	char    *str;
	t_list  *head;

	head = NULL;
    fd = open(file_name, O_RDONLY, 0);
	if (fd > 0)
	{
    	while(get_next_line(fd, &str))
    	{
			map->ht++;
    	    ft_lstadd(&head, ft_lstnew(str, sizeof(str)));
    	    free(str);
    	}
	}
	parse_list(map, head);
	return (head);
}

/*
**	
*/

void	*parse_list(frame *map, t_list *head)
{
	t_list	*temp;
	char	**strs;
	int		i;
	int		c;

	i = -1;
	get_height_from_list(map, head, &temp);
	while (temp)
	{
		c = -1;
		strs = ft_strsplit(temp->content, ' ');
		if (!map->wh)
			while (strs[map->wh])
				map->wh++;
		if (!(map->mx[++i] = (int *)malloc(sizeof(int) * map->wh)))
			return (NULL);
		while (strs[++c])
			map->mx[i][c] = ft_atoi(strs[c]);
		free(strs);
		temp = temp->prev;
	}
	return (map);
}


/*
**	
*/

void	*get_height_from_list(frame *map, t_list *head, t_list **temp)
{
	*temp = head;
	while ((*temp)->next)
		*temp = (*temp)->next;
	if (!(map->mx = (int **)malloc(sizeof(int *) * map->ht)))
		return (NULL);
	return (*temp);
}

/*
**	
*/

void	print_frame(frame *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < map->ht)
	{
		j = 0;
		while (++j < map->wh)
			ft_printf("%2d ", map->mx[i][j]);
		ft_printf("\n");
	}
}
