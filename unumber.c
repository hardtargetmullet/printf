/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 16:56:34 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 01:56:23 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

void		unumber_print(char *str, t_flags *flags, char c)
{
	int size;

	size = ft_strlen(str);
	if (flags->hastag && flags->zero && (c == 'x' || c == 'X'))
	{
		if (c == 'x')
			write(1, "0x", 2);
		else
			write(1, "0X", 2);
		flags->total += 2;
		flags->width -= 2;
	}
	if (flags->neg_sign)
	{
		ft_putstr(str);
		flags->total += size;
		spaces(flags->width - size, flags, 0);
	}
	else
	{
		spaces(flags->width - size, flags, flags->zero);
		ft_putstr(str);
		flags->total += size;
	}
	ft_strdel(&str);
}

static void	unum_prep(uintmax_t num, t_flags *flags)
{
	int		size;
	char	*n;

	size = num_size(num, 10);
	if (flags->pre_amount > size)
		size = flags->pre_amount;
	n = ft_strnew(size);
	n[size] = '\0';
	while (--size >= 0)
	{
		if (num != 0)
			n[size] = num % 10 + '0';
		else
			n[size] = '0';
		num /= 10;
	}
	unumber_print(n, flags, 'u');
}

static void	unum(va_list ap, t_flags *flags, char c)
{
	uintmax_t	num;

	if (c == 'u' && flags->hh_mod)
		num = (unsigned char)va_arg(ap, int);
	else if (c == 'u' && flags->h_mod)
		num = (unsigned short)va_arg(ap, int);
	else if ((c == 'u' && flags->l_mod) || c == 'U')
		num = va_arg(ap, unsigned long);
	else if (c == 'u' && flags->ll_mod)
		num = va_arg(ap, unsigned long long);
	else if (c == 'u' && flags->j_mod)
		num = va_arg(ap, uintmax_t);
	else if (c == 'u' && flags->z_mod)
		num = va_arg(ap, ssize_t);
	else
		num = va_arg(ap, unsigned int);
	if (flags->hastag && num == 0)
		return (char_print('0', flags));
	if (!flags->width && flags->precision && !flags->pre_amount && num == 0)
		return ;
	if (flags->precision && !flags->pre_amount && num == 0)
		return (char_print(' ', flags));
	unum_prep(num, flags);
}

void		unumber(va_list ap, t_flags *flags, char c)
{
	if (c == 'o' || c == 'O')
		onum(ap, flags, c);
	else if (c == 'U' || c == 'u')
		unum(ap, flags, c);
	else if (c == 'x' || c == 'X')
		xnum(ap, flags, c);
}
