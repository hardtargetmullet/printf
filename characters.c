/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:08:34 by anieto            #+#    #+#             */
/*   Updated: 2017/01/25 14:39:19 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

void	char_print(int c, t_flags *flags)
{
	int		i;
	char	d;

	i = 0;
	d = ' ';
	if (flags->zero && !flags->neg_sign)
		d = '0';
	if (flags->neg_sign)
		ft_putchar(c);
	if (flags->width)
	{
		while (i < flags->width - 1)
		{
			ft_putchar(d);
			i++;
		}
	}
	if (!flags->neg_sign)
		ft_putchar(c);
	flags->total += i + 1;
}

char	*wide_to_string(wint_t w)
{
	char *p;

	p = ft_strnew(4);
	if (w <= 0x0ff)
		p[0] = w;
	else if (w <= 0x07ff)
	{
		p[0] = (w >> 6) + 0xc0;
		p[1] = (w & 0x3f) + 0x80;
	}
	else if (w <= 0xFFFF)
	{
		p[0] = (w >> 12) + 0xe0;
		p[1] = ((w >> 6) & 0x3f) + 0x80;
		p[2] = (w & 0x3f) + 0x80;
	}
	else if (w <= 0x10FFFF)
	{
		p[0] = (w >> 18) + 0xf0;
		p[1] = (w >> 12 & 0x3f) + 0x80;
		p[2] = (w >> 6 & 0x3f) + 0x80;
		p[3] = (w & 0x3f) + 0xc80;
	}
	return (p);
}

void	wide_handle(wint_t w, t_flags *flags)
{
	char *s;

	if (w < 0 || (w > 55295 && w < 57344) || w > 1114111)
	{
		flags->total = -1;
		return ;
	}
	s = wide_to_string(w);
	if (w == 0)
		char_print(0, flags);
	else
		string_prep(s, flags);
	ft_strdel(&s);
}

void	characters(va_list ap, t_flags *flags, char spec)
{
	if (spec == 'c' && !flags->l_mod)
		char_print(va_arg(ap, int), flags);
	else
		wide_handle(va_arg(ap, wint_t), flags);
}
