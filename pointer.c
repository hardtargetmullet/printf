/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:09:28 by anieto            #+#    #+#             */
/*   Updated: 2017/01/19 20:54:07 by anieto           ###   ########.fr       */
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
void	pointer(void *v, t_flags *flags)
{
	long n;
	int	size;
	char *p;

	n = (long)v;
	if (n == 0 && flags->precision && !flags->pre_amount)
		return (number_print("0x", flags));
	size = num_size(n, 16) + 2;
	if (flags->pre_amount > size - 2)
		size = flags->pre_amount + 2;
	p = ft_strnew(size);
	p[size] = '\0';
	while (--size >= 0)
	{
		if (n != 0)
			p[size] = ((n % 16) > 9) ? (n % 16) - 10 + 'a': (n % 16) + '0';
		else
			p[size] = '0';
		n /= 16;
	}
	p[1] = 'x';
	p[0] = '0';
	number_print(p, flags);
}

