/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:45:22 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 03:15:38 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

void		how_much(char *s, int len)
{
	int i;

	i = 0;
	while (*s && i < len)
	{
		ft_putchar(*s);
		s++;
		i++;
	}
}

static void	neg_on(char *s, t_flags *flags)
{
	if (flags->precision == 0)
		ft_putstr(s);
	if (flags->precision == 1)
		if (flags->pre_amount != 0)
			how_much(s, flags->pre_amount);
}


void		string_prep(char *s, t_flags *flags)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	if (flags->precision && !(flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->neg_sign)
		neg_on(s, flags);
	if (flags->width > size)
		while (i + size < flags->width)
		{
			if (!flags->zero || flags->neg_sign)
				write(1, " ", 1);
			else
				write(1, "0", 1);
			i++;
		}
	if (flags->precision == 0  && !flags->neg_sign)
		ft_putstr(s);
	if (flags->precision == 1 && !flags->neg_sign)
		if (flags->pre_amount != 0)
			how_much(s, flags->pre_amount);
	flags->total += size + i;
}

void static	long_string(wchar_t *ws, t_flags *flags)
{
	int		total;
	int		len;
	char	*str;
	char	*p;

	p = ft_strnew(4);
	total = 0;
	len = flags->precision ? flags->pre_amount : 2147483647;
	while (ws != NULL && *ws && (total <= len))
	{
		if ((*ws < 0 || (*ws > 55295 && *ws < 57344) || *ws > 1114111)
			&& (flags->total = -1))
			return ;
		total += ft_strlen(str = wide_to_string(*ws++));
		if (total <= len)
		{
			p = ft_re_alloc(p, ft_strlen(p) + ft_strlen(str));
			p = ft_strncat(p, str, ft_strlen(str));
		}
	}
	string_prep(p, flags);
	ft_strdel(&p);
}

void		string(va_list ap, t_flags *flags, char c)
{
	char	*blank;
	char	*s;
	wchar_t	*ws;

	s = 0;
	blank = "(null)";
	if (c == 'S' || (flags->l_mod && c == 's'))
	{
		ws = va_arg(ap, wchar_t *);
		if (ws)
			long_string(ws, flags);
		else
			string_prep(blank, flags);
	}
	else
	{
		s = va_arg(ap, char *);
		if (s)
			string_prep(s, flags);
		else
			string_prep(blank, flags);
	}
}
