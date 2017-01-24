/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 08:34:45 by anieto            #+#    #+#             */
/*   Updated: 2017/01/23 21:02:51 by anieto           ###   ########.fr       */
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

static	int	num_size(uintmax_t num)
{
	int len;

	len = 1;
	while (num/=10)
	{
		len++;
	}
	return (len);
}

static void number_print(char *str, t_flags *flags)
{
	int size;

	size = ft_strlen(str);
	if (flags->neg_sign)
	{
		ft_putstr(str);
		flags->total += size;
		spaces(flags->field_width - size, flags, 0);
	}
	else
	{
		if (flags->zero)
			spaces(flags->field_width - size, flags, 1);
		else
			spaces(flags->field_width - size, flags, 0);
		ft_putstr(str);
		flags->total += size;
	}
}

static int	ft_putchar_ret(int c)
{
	write(1, &c, 1);
	return (1);
}

static void	prep_number(uintmax_t num, t_flags *flags, int prefix)
{
	int		size;
	char	*n;

	size = num_size(num);
	if (flags->pre_amount >= size && !(flags->zero = 0))
		size = flags->pre_amount;
	if (prefix != 0 && !flags->zero)
		size++;
	else if (prefix == '-' && flags->zero && !flags->neg_sign)
		size++;
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
	if (prefix && flags->zero && flags->field_width--)
		flags->total += ft_putchar_ret(prefix);
	else if (prefix)
		n[0] = prefix;
	number_print(n, flags);
}

void		number(va_list ap, t_flags *flags, char c)
{
	intmax_t	num;
	char		prefix;

	if (c == 'D' || flags->l_mod)
		num = va_arg(ap, long);
	else if (flags->hh_mod)
		num = (signed char)va_arg(ap, int);
	else if (flags->h_mod)
		num = (short)va_arg(ap, int);
	else if (flags->ll_mod)
		num = va_arg(ap, long long);
	else if (flags->j_mod)
		num = va_arg(ap, intmax_t);
	else if (flags->z_mod)
		num = va_arg(ap, ssize_t);
	else
		num = va_arg(ap, int);
	prefix = (flags->pos_sign) ? '+': 0;
	prefix = (flags->space && (!flags->pos_sign)) ? ' ': prefix;
	prefix = ((num < 0) && (num *= -1)) ? '-': prefix;
	if (num == 0 && !flags->field_width && flags->precision && !flags->pre_amount)
		return ;
	if (num == 0 && flags->field_width && !flags->pre_amount)
		return (char_print(' ', flags));
	prep_number((uintmax_t)num, flags, prefix);
}
