/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:17:22 by eshor             #+#    #+#             */
/*   Updated: 2020/05/05 23:47:14 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	char_align(char c, int w, char side, char filler)
{
	int i;

	if (side == 'l')
	{
		ft_putchar(c);
		i = 1;
		while (i < w)
		{
			ft_putchar(filler);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < w - 1)
		{
			ft_putchar(filler);
			i++;
		}
		ft_putchar(c);
	}
}

int		print_char(t_lst *temp, int c, int *w_p)
{
	char	ch;
	int		len;
	char	filler;
	char	side;

	ch = (char)c;
	filler = ' ';
	if (w_p[0] != 0)
	{
		if (temp->flags[2] != '-' && temp->flags[0] == '0')
			filler = '0';
		if (temp->flags[2] == '-')
			side = 'l';
		else
			side = 'r';
		char_align(ch, w_p[0], side, filler);
	}
	else
		ft_putchar(ch);
	len = (w_p[0] > 0) ? w_p[0] : 1;
	return (len);
}

int		print_str(t_lst *temp, char *str, int *w_p)
{
	int len;

	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (w_p[1] < (int)ft_strlen(str) && w_p[1] != -1)
		str = shorten_str(str, w_p[1]);
	if (w_p[0] != 0 && w_p[0] > (int)ft_strlen(str))
		str = align_width(str, w_p[0], temp);
	ft_putstr(str);
	len = (int)ft_strlen(str);
	ft_strdel(&str);
	return (len);
}

int		print_ptr(t_lst *temp, void *ptr, int *w_p)
{
	int		len;
	char	*str;

	len = 0;
	temp->flags[4] = '#';
	if ((unsigned long long)ptr == 0 && w_p[1] == 0)
	{
		str = ft_strdup("0x");
		if (w_p[0] != 0)
		{
			str = int_width(str, w_p[0], temp);
		}
		len = (int)ft_strlen(str);
		ft_putstr(str);
		ft_strdel(&str);
		return (len);
	}
	else
		return (print_uint(temp, (unsigned long long)ptr, w_p));
}
