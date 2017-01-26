/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 01:55:42 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 01:56:29 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static void	onum_prep(uintmax_t num, t_flags *flags, int prefix)
{
	int		size;
	char	*n;

	size = num_size(num, 8);
	if (prefix && num)
		size++;
	if (flags->pre_amount > size)
		size = flags->pre_amount;
	n = ft_strnew(size);
	n[size] = '\0';
	while (--size >= 0)
	{
		if (num != 0)
			n[size] = num % 8 + '0';
		else
			n[size] = '0';
		num /= 8;
	}
	unumber_print(n, flags, 'o');
}

static void	xnum_prep(uintmax_t n, t_flags *flags, char c)
{
	int		size;
	char	*p;

	size = num_size(n, 16);
	n == 0 ? flags->hastag = 0 : 0;
	if (flags->pre_amount > size)
		size = flags->pre_amount;
	size += (flags->hastag && !flags->zero) ? 2 : 0;
	p = ft_strnew(size);
	p[size] = '\0';
	while (--size >= 0)
	{
		if (n != 0)
			p[size] = ((n % 16) > 9) ? (n % 16) - 10 + 'a' : (n % 16) + '0';
		else
			p[size] = '0';
		n /= 16;
	}
	if (flags->hastag && !flags->zero)
	{
		p[1] = 'x';
		p[0] = '0';
	}
	c == 'X' ? ft_capitalize(p) : 0;
	unumber_print(p, flags, c);
}

void		onum(va_list ap, t_flags *flags, char c)
{
	uintmax_t	num;
	int			prefix;

	if (c == 'o' && flags->hh_mod)
		num = (unsigned char)va_arg(ap, int);
	else if (c == 'o' && flags->h_mod)
		num = (unsigned short)va_arg(ap, int);
	else if ((c == 'o' && flags->l_mod) || c == 'O')
		num = va_arg(ap, unsigned long);
	else if (c == 'o' && flags->ll_mod)
		num = va_arg(ap, unsigned long long);
	else if (c == 'o' && flags->j_mod)
		num = va_arg(ap, uintmax_t);
	else if (c == 'o' && flags->z_mod)
		num = va_arg(ap, ssize_t);
	else
		num = va_arg(ap, unsigned int);
	prefix = flags->hastag ? '0' : 0;
	if (flags->hastag && num == 0)
		return (char_print('0', flags));
	if (!flags->width && flags->precision && !flags->pre_amount && num == 0)
		return ;
	if (flags->precision && !flags->pre_amount && num == 0)
		return (char_print(' ', flags));
	onum_prep(num, flags, prefix);
}

void		xnum(va_list ap, t_flags *flags, char c)
{
	uintmax_t	num;

	if (flags->hh_mod)
		num = (unsigned char)va_arg(ap, int);
	else if (flags->h_mod)
		num = (unsigned short)va_arg(ap, int);
	else if (flags->l_mod)
		num = va_arg(ap, unsigned long);
	else if (flags->ll_mod)
		num = va_arg(ap, unsigned long long);
	else if (flags->j_mod)
		num = va_arg(ap, uintmax_t);
	else if (flags->z_mod)
		num = va_arg(ap, ssize_t);
	else
		num = va_arg(ap, unsigned int);
	if (num == 0 && !flags->width && flags->precision && !flags->pre_amount)
		return ;
	if (num == 0 && flags->precision && !flags->pre_amount)
		return (char_print(' ', flags));
	xnum_prep(num, flags, c);
}
