/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:39:21 by anieto            #+#    #+#             */
/*   Updated: 2017/01/23 16:03:47 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# include <locale.h>
# include <wchar.h>

typedef struct	s_flags
{
	int			neg_sign;
	int			pos_sign;
	int			space;
	int			hastag;
	int			zero;
	int			field_width;
	int			precision;
	int			pre_amount;
	int			h_mod;
	int			hh_mod;
	int			l_mod;
	int			ll_mod;
	int			j_mod;
	int			z_mod;
	int			total;
}				t_flags;

int				ft_printf(const char *fmt, ...);
int				printer(char const *fmt, va_list ap, t_flags *flags);
void			string(va_list ap, t_flags *flags, char c);
void			characters(va_list ap, t_flags *flags, char spec);
void			number(va_list ap, t_flags *flags, char c);
void			unumber(va_list ap, t_flags *flags, char c);
void			pointer(void *v, t_flags *flags);
void			binary(long long num, t_flags *flags);
void			string_prep(char *s, t_flags *flags);
char			*wide_to_string(wint_t w);
void			wide_handle(wint_t w, t_flags *flags);
int				ft_ismodflag(int c);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
char			*ft_strnew(size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
char			*ft_itoa_base(int value, int base);
char			*ft_ltoa_base(long long value, int base);
char			*ft_utoa_base(unsigned long long value, int base, int lc);
char			*ft_utoa(unsigned long long n);
char			*ft_otoa(unsigned long long n);
char			*ft_strdup(const char *s1);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putnbr(int c);
void			how_much(char *s, int len);
void			char_print(int c, t_flags *flags);
#endif
