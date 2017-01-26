/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:13:19 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 02:58:16 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static void	set_width(char const **fmt, t_flags *flags, va_list ap)
{
	flags->width = ft_atoi(*fmt);
	while (ft_isdigit(**fmt))
		*fmt += 1;
	if (**fmt == '*')
	{
		flags->width = va_arg(ap, int);
		*fmt += 1;
	}
	if (flags->width < 0)
	{
		flags->neg_sign = 1;
		flags->width *= -1;
	}
}

static void	set_precision(char const **fmt, t_flags *flags, va_list ap)
{
	*fmt += 1;
	flags->precision = 1;
	flags->pre_amount = ft_atoi(*fmt);
	while (ft_isdigit(**fmt))
		*fmt += 1;
	if (**fmt == '*')
	{
		flags->pre_amount = va_arg(ap, int);
		*fmt += 1;
	}
	if (flags->pre_amount < 0)
		flags->precision = 0;
}

void		set_flags(char const *fmt, t_flags *flags, va_list ap)
{
	while (*fmt && !ft_isalpha(*fmt) && *fmt != '%')
	{
		if (*fmt == '-')
			flags->neg_sign = 1;
		else if (*fmt == '+')
			flags->pos_sign = 1;
		else if (*fmt == ' ')
			flags->space = 1;
		else if (*fmt == '#')
			flags->hastag = 1;
		else if (*fmt == '0')
			flags->zero = 1;
		else if (ft_isdigit(*fmt) || *fmt == '*')
			set_width(&fmt, flags, ap);
		if (*fmt == '.')
			set_precision(&fmt, flags, ap);
		if (*fmt && !ft_isalpha(*fmt))
			fmt++;
	}
}
