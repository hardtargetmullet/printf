/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:09:28 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 01:41:15 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static void	number_print2(char *str, t_flags *flags)
{
	int size;

	size = ft_strlen(str);
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

void		pointer(void *v, t_flags *flags)
{
	long	n;
	int		size;
	char	*p;

	n = (long)v;
	if (n == 0 && flags->precision && !flags->pre_amount)
		return (number_print2(ft_strdup("0x"), flags));
	size = num_size(n, 16) + 2;
	if (flags->pre_amount > size - 2)
		size = flags->pre_amount + 2;
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
	p[1] = 'x';
	p[0] = '0';
	number_print2(p, flags);
}
