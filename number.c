/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 08:34:45 by anieto            #+#    #+#             */
/*   Updated: 2017/01/15 14:25:50 by anieto           ###   ########.fr       */
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
	while (i + size < w)
	{
		ft_putchar(c);
		i++;
	}
	if (flags->pos_sign && !flags->neg_sign && !flags->zero && num > 0)
		ft_putchar('+');
	flags->total += i;
	return (0);
}

static void	number_print(long long num, t_flags *flags)
{
	int		size;
	char	*n;

	n = ft_ltoa_base(num, 10);
	size = ft_strlen(n);
	if (flags->precision && !(flags->pre_amount > size))
		size = flags->pre_amount;
	if (flags->space && !flags->pos_sign && num > 0)
		ft_putchar(' ');
	if (flags->neg_sign)
	{
		if (flags->pos_sign && num > 0)
			ft_putchar('+');
		if (flags->precision == 0)
			ft_putstr(n);
	}
	if (flags->field_width > size)
		flags->total += spaces(num, size, flags);
	if (flags->precision == 0 && !flags->neg_sign)
		ft_putstr(n);
	if (flags->precision == 1 && !flags->neg_sign)
		if (flags->pre_amount != 0 || (!flags->pre_amount && num != 0))
			ft_putstr(n);
	flags->total += size;
}

void		number(va_list ap, t_flags *flags, char c)
{
	if (flags->hh_mod)
		number_print((signed char)va_arg(ap, int), flags);
	else if (flags->h_mod)
		number_print((short)va_arg(ap, int),flags);
	else if ((flags->l_mod && (c == 'd' || c == 'i')) || c == 'D')
		number_print(va_arg(ap, long), flags);
	else if (flags->ll_mod)
		number_print(va_arg(ap, long long), flags);
	else if (flags->j_mod)
		number_print(va_arg(ap, intmax_t), flags);
	else if (flags->z_mod)
		number_print(va_arg(ap, size_t), flags);
	else
		number_print(va_arg(ap, int), flags);
}
