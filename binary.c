/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 20:23:46 by anieto            #+#    #+#             */
/*   Updated: 2017/01/05 22:18:45 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static int	spaces(int num, int size, t_flags *flags)
{
	int i;
	int w;
	int c;

	i = 0;
	if (num < 0)
		w = flags->field_width;
	else
		w = flags->field_width - flags->pos_sign - flags->space;
	if (flags->zero && !flags->neg_sign)
		c = 48;
	else
		c = 32;
	if (flags->pos_sign && flags->zero && num > 0)
		ft_putchar('+');
	while(i + size < w)
	{
		ft_putchar(c);
		i++;
	}
	if (flags->pos_sign && !flags->neg_sign && !flags->zero && num > 0)
		ft_putchar('+');
	return (0);
}

void		binary(long long num, t_flags *flags)
{
	int		size;
	char	*n;

	n = ft_ltoa_base(num, 2);
	size = ft_strlen(n);
	if (flags->precision && !(flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->space)
		ft_putchar(' ');
	if (flags->neg_sign)
	{
		if (flags->pos_sign && num > 0)
			ft_putchar('+');
		if (flags->precision == 0)
			ft_putstr(n);
	}
	if (flags->field_width > size)
		spaces(num, size, flags);
	if (flags->precision == 0 && !flags->neg_sign)
		ft_putstr(n);
	if (flags->precision == 1 && !flags->neg_sign)
		if (flags->pre_amount != 0 || (!flags->pre_amount && num != 0))
			ft_putstr(n);
}
