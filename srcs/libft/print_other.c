/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:08:36 by eshor             #+#    #+#             */
/*   Updated: 2020/05/05 23:47:25 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_other(t_lst *temp, int *w_p)
{
	if (temp->type == 0)
		return (0);
	else
		return (print_char(temp, temp->type, w_p));
}
