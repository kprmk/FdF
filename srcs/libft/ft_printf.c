/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:18:28 by mbrogg            #+#    #+#             */
/*   Updated: 2020/05/05 23:46:42 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_from_list(const char *format, t_lst *head, va_list ap, int i)
{
	t_lst	*temp;
	int		res;

	temp = head;
	res = 0;
	while (temp)
	{
		while (i < temp->pos)
		{
			ft_putchar(format[i]);
			i++;
			res++;
		}
		res += print_elem(temp, ap);
		i = temp->next_pos;
		temp = temp->next;
	}
	while (i < (int)ft_strlen(format))
	{
		ft_putchar(format[i]);
		i++;
		res++;
	}
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			*pos;
	int			amount;
	t_lst		*head;
	int			res;

	amount = 0;
	va_start(ap, format);
	pos = count_args(format, &amount);
	res = 0;
	if (amount != 0)
	{
		head = create_list(format, pos, amount);
		res = print_from_list(format, head, ap, 0);
	}
	else
	{
		ft_putstr(format);
		res = (int)ft_strlen(format);
	}
	va_end(ap);
	if (amount != 0)
		lst_del(&head);
	free(pos);
	return (res);
}
