/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 16:56:34 by anieto            #+#    #+#             */
/*   Updated: 2017/01/15 14:16:30 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static int		spaces2(int num, int size, t_flags *flags)
{
	int i;
	int w;
	int c;

	i = 0;
	if (num < 0)
		w = flags->field_width;
	else
		w = flags->field_width - flags->hastag;
	if (flags->zero && !flags->neg_sign)
		c = 48;
	else
		c = 32;
	if (flags->hastag && flags->zero && flags->neg_sign)
		ft_putchar('0');
	while(i + size < w)
	{
		ft_putchar(c);
		i++;
	}
	if (flags->hastag && !flags->neg_sign)
		ft_putchar('0');
	flags->total += i;
	return (0);
}

static void		onum(unsigned long long num, t_flags *flags)
{
	int		size;
	char	*n;

	n = ft_otoa(num);
	size = ft_strlen(n);
	if (flags->precision && !(flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->neg_sign)
	{
		if (flags->precision == 0)
			ft_putstr(n);
	}
	if (flags->field_width > size)
		spaces2(num, size, flags);
	if (flags->precision)
	{
		if (flags->hastag && !flags->pre_amount && num)
			ft_putchar('0');
		if (num)
			ft_putstr(n);
	}
	if (flags->precision == 0 && !flags->neg_sign)
		//if (flags->pre_amount != 0 || (!flags->pre_amount && num != 0))
		{
			if (flags->hastag && num != 0)
				ft_putchar('0');
			ft_putstr(n);
		}
	flags->total += size;
}

static int		spaces(int size, t_flags *flags)
{
	int i;
	int c;

	i = 0;
	if (flags->zero && !flags->neg_sign)
		c = 48;
	else
		c = 32;
	while(i + size < flags->field_width)
	{
		ft_putchar(c);
		i++;
	}
	flags->total += i;
	return (0);
}

static void		unum(unsigned long long num, t_flags *flags)
{
	int		size;
	char	*n;

	n = ft_utoa(num);
	size = ft_strlen(n);
	if (flags->precision && (flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->neg_sign)
	{
		if (flags->precision == 0 && num != 0)
			ft_putstr(n);
	}
	if (flags->field_width > size)
		spaces(size, flags);
	if (flags->precision && num != 0)
		ft_putstr(n);
	if (flags->precision == 0 && !flags->neg_sign)
		ft_putstr(n);
	flags->total += size;
}

static int		pre_num(int lc, t_flags* flags)
{
	if (lc)
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
	flags->total += 2;
	return (0);
}

static int		spaces3(int size, t_flags *flags, int lc)
{
	int i;
	int w;
	int c;

	i = 0;
	if (flags->hastag)
		w = flags->field_width - 2;
	else
		w = flags->field_width - flags->hastag;
	if (flags->zero && !flags->neg_sign)
		c = 48;
	else
		c = 32;
	if (flags->hastag && flags->zero && flags->field_width && !flags->neg_sign)
		pre_num(lc, flags);
	while(i + size < w)
	{
		ft_putchar(c);
		i++;
	}
	if (flags->hastag && !flags->neg_sign && !flags->zero)
		pre_num(lc, flags);
	flags->total += i;
	return (0);
}

static void		xnum(unsigned long long num, t_flags *flags, int lc)
{
	int		size;
	char	*n;

	n = ft_utoa_base(num, 16, lc);
	size = ft_strlen(n);
	if (flags->precision && (flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->neg_sign)
	{
		if (flags->hastag)
			pre_num(lc, flags);
		if (flags->precision == 0)
			ft_putstr(n);
	}
	if (flags->field_width > size)
		spaces3(size, flags, lc);
	//if (flags->precision && num != 0)
	if (flags->precision && num != 0)
	{
		if (flags->hastag && !flags->pre_amount && num != 0)
			pre_num(lc, flags);
		ft_putstr(n);
	}
	if (flags->precision == 0 && !flags->neg_sign)
		//if (flags->pre_amount != 0 || (!flags->pre_amount && num != 0))
		{
			if (flags->hastag && !flags->zero && !flags->field_width && num != 0)
				pre_num(lc, flags);
			ft_putstr(n);
		}
	flags->total += size;
}

void		unumber(va_list ap, t_flags *flags, char c)
{
	if (c == 'o' && (flags->hh_mod || flags->h_mod || flags->l_mod))
		onum(va_arg(ap, unsigned int), flags);
	//if (c == 'o' && flags->l_mod)
	//	onum(va_arg(ap, unsigned int), flags);
	if (c == 'o' && (flags->ll_mod || flags->j_mod))
		onum(va_arg(ap, unsigned long long), flags);
	if (c == 'o' && flags->z_mod)
		onum(va_arg(ap, size_t), flags);
	if (c == 'o' || c == 'O')
		onum(va_arg(ap, unsigned long long), flags);	
	if (c == 'U')
		unum(va_arg(ap, unsigned long), flags);
	else if (c == 'u' && flags->hh_mod)
		unum((unsigned char)va_arg(ap, unsigned int), flags);
	else if (c == 'u' && flags->l_mod)
		unum(va_arg(ap, unsigned long), flags);
	else if (c == 'u' && flags->ll_mod)
		unum(va_arg(ap, unsigned long long), flags);
	else if (c == 'u' && flags->z_mod)
		unum(va_arg(ap, size_t), flags);
	else if (c == 'u' && flags->j_mod)
		unum(va_arg(ap, uintmax_t), flags);
	else if (c == 'u')
		unum(va_arg(ap, unsigned int), flags);
	if (c == 'x' && flags->h_mod)
		xnum((unsigned short)va_arg(ap, unsigned int), flags, 1);
	else if (c == 'x' && flags->hh_mod)
		xnum((unsigned char)va_arg(ap, unsigned int), flags, 1);
	else if (c == 'x' && flags->l_mod)
		xnum(va_arg(ap, unsigned long), flags, 1);
	else if (c == 'x' && flags->ll_mod)
		xnum(va_arg(ap, unsigned long long), flags, 1);
	else if (c == 'x' && flags->z_mod)
		xnum(va_arg(ap, size_t), flags, 1);
	else if (c == 'x' && flags->j_mod)
		xnum(va_arg(ap, uintmax_t), flags, 1);
	else if (c == 'x')
		xnum(va_arg(ap, unsigned int), flags, 1);
	if (c == 'X' && flags->h_mod)
		xnum((unsigned short)va_arg(ap, unsigned int), flags, 0);
	else if (c == 'X' && flags->hh_mod)
		xnum((unsigned char)va_arg(ap, unsigned int), flags, 0);
	else if (c == 'X' && flags->l_mod)
		xnum(va_arg(ap, unsigned long), flags, 0);
	else if (c == 'X' && flags->ll_mod)
		xnum(va_arg(ap, unsigned long long), flags, 0);
	else if (c == 'X' && flags->z_mod)
		xnum(va_arg(ap, size_t), flags, 0);
	else if (c == 'X')
		xnum(va_arg(ap, unsigned int), flags, 0);
}
