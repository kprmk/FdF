/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprmk <kprmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:36:21 by mbrogg            #+#    #+#             */
/*   Updated: 2020/07/09 22:53:25 by kprmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>

# define BUFF_SIZE 5

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void	*dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dst, const char *src, unsigned long long n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strjoin_s(char **str, char *buf);
char			*ft_spaces(char *s);
char			*ft_spaces_rev(char *s);
size_t			ft_strisempty(const char *s);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n, int *amount);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
char			**ft_free_split(char **ar, int i);

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t content_size);

void			ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
t_list			*ft_lstnew_fd(size_t fd);
size_t			ft_lstdelone_s(t_list **head, t_list **alst);
void			ft_lstdel(t_list **alst, void(*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void(*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				get_next_line(const int fd, char **line);


/* ************************************************************************** */
//								FT_PRINTF                                     //
/* ************************************************************************** */

typedef	struct					s_lst
{
	int				pos;
	int				index;
	char			flags[5];
	char			*width;
	char			*precision;
	char			length[2];
	char			type;
	int				next_pos;
	int				stars;
	struct s_lst	*next;
}								t_lst;

typedef unsigned long long int	t_ulli;

typedef struct					s_ldbl_struct
{
	t_ulli			mant : 64;
	unsigned int	exp : 15;
	unsigned int	sign : 1;
}								t_ldbl_struct;

typedef union					u_ldbl
{
	long double		origin;
	t_ldbl_struct	parts;
}								t_ldbl;

typedef struct					s_lan
{
	int				*num;
	int				len;
}								t_lan;

typedef struct					s_lanch
{
	char			*num;
	int				len;
}								t_lanch;

int								ft_printf(const char *format, ...);

t_lst							*new(int pos);
int								lst_push_front(t_lst **head, t_lst *new);
void							lst_reverse(t_lst **head);
void							lst_del(t_lst **head);

int								type_pos(const char *format, int pos);
void							change_case(char **str);
char							*fill_number(const char *format,
int *pos, int *len,
char w_or_p);
char							*find_w_or_p(const char *format,
int len, int temp);
int								*count_args(const char *format,
int *amount);
int								find_flags(const char *format,
int pos, t_lst **node);
int								find_width(const char *format,
int pos, t_lst **node);
int								find_prec(const char *format,
int pos, t_lst **node);
int								find_length(const char *format,
int pos, t_lst **node);
int								find_type(const char *format,
int pos, t_lst **node);

int								print_elem(t_lst *temp, va_list ap);
int								print_elem1(t_lst *temp, va_list ap, int *w_p);
int								print_elem2(t_lst *temp, va_list ap, int *w_p);
int								print_elem3(t_lst *temp, va_list ap, int *w_p);

int								print_char(t_lst *temp, int c, int *w_p);
int								print_str(t_lst *temp, char *str, int *w_p);
int								print_ptr(t_lst *temp,
void *ptr, int *w_p);

void							add_s_or_p(char **str,
t_lst *temp, long long int nbr);
void							zero_flag(char **str,
long long int nbr, t_lst *temp, int *w_p);
void							prec_greater(char **str,
t_lst **temp, int *w_p);
void							prec_no_width(char **str,
t_lst *temp, long long int nbr, int *w_p);
char							*create_str(long long int nbr,
int *w_p);
void							add_and_change(char **str,
long long int nbr, t_lst **temp);
void							prec_and_width(t_lst **temp,
char **str, int *w_p);

int								print_int(t_lst *temp,
long long int nbr, int *w_p);
int								print_long(t_lst *temp,
long nbr, int *w_p);
int								print_long_long(t_lst *temp,
long long nbr, int *w_p);
int								print_short(t_lst *temp, int nbr, int *w_p);
int								print_sshort(t_lst *temp, int nbr, int *w_p);

char							*create_str_u(unsigned long long nbr,
t_lst **temp, int *w_p, char *flag);
void							prec_u(char **str, t_lst *temp, int *w_p);
void							width_u(char **str, t_lst *temp, int *w_p,
t_ulli nbr);

int								print_uint(t_lst *t,
unsigned long long int n, int *w_p);
int								print_ulong(t_lst *temp,
unsigned long nbr, int *w_p);
int								print_ulong_long(t_lst *temp,
unsigned long long nbr, int *w_p);
int								print_ushort(t_lst *temp,
unsigned int nbr, int *w_p);
int								print_usshort(t_lst *temp, int nbr, int *w_p);

char							*lfloat(long double input, int prec);
int								print_float(t_lst *temp,
double input, int *w_p);
int								print_lfloat(t_lst *temp,
long double input, int *w_p);

int								create_lanch_from_bitstr(t_lanch **res,
char *str, int prec);
t_lanch							*cpy_lanch(t_lanch **src, int dst_len);
t_lanch							*sum_lanch_nums(t_lanch *f, t_lanch *s);
t_lanch							*power_of_five_lanch(int num, int width);
t_lanch							*create_lanch(t_lanch *res, int width);
int								precision_in_da_house(t_lanch *res, int prec);
int								increas_lanch_one(t_lanch *res, int c);
char							*str_from_db(t_lan *i_db,
t_lanch *f_db, int prec, int sign);
char							*ft_dtoa_two(t_ulli value,
int shift, int *res_len);
char							*lfloat(long double input, int prec);
t_lan							*create_lan_from_bitstr(char *str);
t_lan							*power_of_two_lan(int num);
t_lan							*sum_lan_nums(t_lan *f, t_lan *s);
void							ft_strrev(char **str);
int								ft_str_is_null_value(char *str);
int								check_inf_nan(t_ldbl *res);

int								print_other(t_lst *temp, int *w_p);
t_lst							*create_list(const char *format,
int *pos, int amount);

char							*align_width(char *str, int size, t_lst *node);
char							*shorten_str(char *str, int precision);
char							*int_width(char *str, int size, t_lst *node);
char							*add_plus(char *str, char to_add);
char							*add_zero(char *str, char type, int i);

char							*ft_itoa_long(long long n);
char							*ft_itoa_base(unsigned long long value,
unsigned long long base);
int								print_inf_nan(char **str, int w, t_lst *temp);
t_lanch							*sum_lanch_nums_init(t_lanch *f, t_lanch *s);
int								if_ones_zeros(unsigned num, int amount,
int type);
/* ************************************************************************** */


#endif
