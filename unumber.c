/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 16:56:34 by anieto            #+#    #+#             */
/*   Updated: 2017/01/19 20:19:13 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static void	spaces(int n, t_flags *flags, int c)
{
	int i;
	
	i = 0;
	if (c)
		c = '0';
	else 
		c = ' ';
	if (n > 0)
	{
		while (i < n)
		{
			ft_putchar(c);
			i++;
		}
		flags->total += i;
	}
}

static	int	num_size(uintmax_t num, int base)
{
	int len;

	len = 1;
	while (num /= base)
	{
		len++;
	}
	return (len);
}

static void number_print(char *str, t_flags *flags, char c)
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
		flags->field_width -= 2;
	}
	if (flags->neg_sign)
	{
		ft_putstr(str);
		flags->total += size;
		spaces(flags->field_width - size, flags, 0);
	}
	else
	{
		//if (flags->zero)
		spaces(flags->field_width - size, flags, flags->zero);
		//else
		//	spaces(flags->field_width - size, flags, 0);
		ft_putstr(str);
		flags->total += size;
	}
}

static char	*ft_capitalize(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
	return (str);
}

static void	xnum_prep(uintmax_t num, t_flags *flags, char c)
{
	int		size;
	char	*n;

	size = num_size(num, 16);
	num == 0 ? flags->hastag = 0 : 0;
	if (flags->pre_amount > size)
		size = flags->pre_amount;
	size += (flags->hastag && !flags->zero) ? 2 : 0;
	n = ft_strnew(size);
	n[size] = '\0';
	while (--size >= 0)
	{
		if (num != 0)
			n[size] = ((num % 16) > 9) ? (num % 16) - 10 + 'a': (num % 16) + '0';
		else
			n[size] = '0';
		num /= 16;
	}
	if (flags->hastag && !flags->zero)
	{
		n[1] = 'x';
		n[0] = '0';
	}
	c == 'X' ? ft_capitalize(n): 0;
	number_print(n, flags, c);
}

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
	number_print(n, flags, 'o');
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
	number_print(n, flags, 'u');
}
/*
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

static void		xnum_prep(unsigned long long num, t_flags *flags, int lc)
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
	if (flags->precision && num != 0)
	{
		if (flags->hastag && !flags->pre_amount && num != 0)
			pre_num(lc, flags);
		ft_putstr(n);
	}
	if (flags->precision == 0 && !flags->neg_sign)
	{
		if (flags->hastag && !flags->zero && !flags->field_width && num != 0)
			pre_num(lc, flags);
		ft_putstr(n);
	}
	flags->total += size;
}
*/
/*
static void xnum(va_list ap, t_flags *flags, int lc)
{
	uintmax_t	num;

	if (flags->h_mod)
		num = (unsigned short)va_arg(ap, unsigned int);
	else if (flags->hh_mod)
		num = (unsigned char)va_arg(ap, unsigned int);
	else if (flags->l_mod)
		num = va_arg(ap, unsigned long);
	else if (flags->ll_mod)
		num = va_arg(ap, unsigned long long);
	else if (flags->z_mod)
		num = va_arg(ap, size_t);
	else if (flags->j_mod)
		num = va_arg(ap, uintmax_t);
	else
		num = va_arg(ap, unsigned int);
	if (num == 0 && flags->hastag && flags->precision && !flags->pre_amount)
		return ;
	if (num == 0 && !flags->field_width && flags->precision && !flags->pre_amount)
		return ;
	if (num == 0 && flags->field_width && flags->precision && !flags->pre_amount)
		return (char_print(' ', flags));
	xnum_prep(num, flags, lc);
}
*/
static void xnum(va_list ap, t_flags *flags, char c)
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
	if (num == 0 && !flags->field_width && flags->precision && !flags->pre_amount)
		return ;
	if (num == 0 && flags->precision && !flags->pre_amount)
		return (char_print(' ', flags));
	xnum_prep(num, flags, c);
}

static void onum(va_list ap, t_flags *flags, char c)
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
	if (!flags->field_width && flags->precision && !flags->pre_amount && num == 0)
		return ;
	if (flags->precision && !flags->pre_amount && num == 0)
		return (char_print(' ', flags));
	onum_prep(num, flags, prefix);
}

static void unum(va_list ap, t_flags *flags, char c)
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
	if (!flags->field_width && flags->precision && !flags->pre_amount && num == 0)
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
