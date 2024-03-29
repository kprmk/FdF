/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_floats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:02:56 by mbrogg            #+#    #+#             */
/*   Updated: 2020/05/05 23:47:10 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dtoa_two(t_ulli value, int shift, int *res_len)
{
	char		*str;
	unsigned	i;
	int			flag;

	i = 0;
	flag = shift < 0 ? -shift : 0;
	if (value == 0)
		return (ft_strdup("0"));
	if (!(str = (char*)malloc(sizeof(char) * (64 + flag + *res_len + 1))))
		exit(1);
	while ((*res_len)-- > 0)
		str[i++] = '0';
	while (value > 0 || i < 64)
	{
		str[i++] = value % 2 + '0';
		value = value / 2;
	}
	while (--flag > 0)
		str[i++] = '0';
	str[i] = '\0';
	ft_strrev(&str);
	*res_len = ft_strlen(str);
	return (str);
}

char	*str_from_db_after_loop(t_lan *i_db, t_lanch *f_db, char *res, int *ar)
{
	if (ar[5] != 0)
	{
		res[(ar[2])++] = '.';
		ar[0] = 0;
		if (f_db != NULL)
		{
			ar[1] = f_db->len - 1;
			while (ar[1] > -1 && ++(ar[0]) <= ar[5])
				res[(ar[2])++] = f_db->num[(ar[1])--] + '0';
		}
		while (++(ar[0]) <= ar[5])
			res[(ar[2])++] = '0';
	}
	res[ar[2]] = '\0';
	free(i_db->num);
	if (f_db != NULL)
	{
		free(f_db->num);
		free(f_db);
	}
	free(i_db);
	free(ar);
	return (res);
}

char	*str_from_db_init(int pc, int idb_len, int **ar, int sn)
{
	char	*res;

	if (((*ar) = (int *)malloc(sizeof(int) * 6)) == NULL)
		exit(1);
	(*ar)[1] = idb_len;
	(*ar)[2] = 0;
	(*ar)[3] = 0;
	(*ar)[5] = pc;
	if (!(res = (char *)malloc(sizeof(char) * (idb_len * 4 + sn + pc + 2))))
		exit(1);
	if (sn == 1)
		res[((*ar)[2])++] = '-';
	return (res);
}

/*
**	arr - > 0 - i, 1 - j, 2 - c, 3 - len, 4 - amount, 5 - prec
*/

char	*str_from_db(t_lan *i_db, t_lanch *f_db, int pc, int sn)
{
	char	*res;
	char	*temp;
	int		*ar;

	res = str_from_db_init(pc, i_db->len, &ar, sn);
	while (--(ar[1]) >= 0)
	{
		ar[0] = -1;
		if (i_db->num[ar[1]] == 0)
			while (++(ar[0]) < 4)
				res[(ar[2])++] = 0 + '0';
		else
		{
			temp = ft_itoa(i_db->num[ar[1]], &ar[4]);
			sn = 4 - ar[4];
			while (sn-- > 0 && (ar[1]) != i_db->len - 1)
				res[(ar[2])++] = '0';
			ft_strcpy(res + ar[2], temp);
			free(temp);
			ar[2] += ar[4];
		}
	}
	return (str_from_db_after_loop(i_db, f_db, res, ar));
}
