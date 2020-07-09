/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:35:39 by mbrogg            #+#    #+#             */
/*   Updated: 2020/07/09 22:53:17 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_split(char **ar, int i)
{
	int	j;

	j = 0;
	if (i != -1)
	{
		while (j != i)
		{
			free(ar[j]);
			j++;
		}
	}
	else
	{
		while (ar[j])
		{
			free(ar[j]);
			j++;
		}
	}
	free(ar);
	return (NULL);
}
