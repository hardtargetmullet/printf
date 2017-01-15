/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:56:46 by anieto            #+#    #+#             */
/*   Updated: 2017/01/12 07:13:46 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

void	init_flags(t_flags *flags)
{
	flags->neg_sign = 0;
	flags->pos_sign = 0;
	flags->space = 0;
	flags->hastag = 0;
	flags->zero = 0;
	flags->field_width = 0;
	flags->precision = 0;
	flags->pre_amount = 0;
	flags->h_mod = 0;
	flags->hh_mod = 0;
	flags->l_mod = 0;
	flags->ll_mod = 0;
	flags->j_mod = 0;
	flags->z_mod = 0;	
}

int	ft_ismodflag(int c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

void		set_flags(char const *fmt, t_flags *flags)
{
	while (*fmt && !ft_isalpha(*fmt))
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
		else if (*fmt >= '1' && *fmt <= '9')
		{
			flags->field_width = ft_atoi(fmt);	
			while (ft_isdigit(*fmt))
				fmt++;
		}
		if (*fmt == '.')
		{
			fmt++;
			flags->precision = 1;
			flags->pre_amount = ft_atoi(fmt);
			while (ft_isdigit(*fmt))
				fmt++;
		}
		if (*fmt)
			fmt++;
	}
}

static void	set_mod_flags(char const *fmt, t_flags *flags)
{
	int i;

	i = 0;
	if (fmt[0] == 'h' && fmt[1] && fmt[1] != 'h')
		flags->h_mod = 1;
	else if (fmt[0] == 'h' && fmt[1] && fmt[1] == 'h')
		flags->hh_mod = 1;
	else if (fmt[0] == 'l' && fmt[1] && fmt[1] != 'l')
		flags->l_mod = 1;
	else if (fmt[0] == 'l' && fmt[1] && fmt[1] == 'l')
		flags->ll_mod = 1;
	else if (fmt[0] == 'j')
		flags->j_mod = 1;
	else if (fmt[0] == 'z')
		flags->z_mod = 1;
}

static void specifier(char c, va_list ap, t_flags *flags)
{
	if (c == '%')
		char_print('%', flags);
	if (c == 'c' || c == 'C')
		characters(ap, flags, c);
	if (c == 's' || c == 'S')
		string(va_arg(ap, char *), flags);
	if (c == 'i' || c == 'd' || c == 'D')
		number(ap, flags, c);
	if (c == 'o' || c == 'x' || c == 'u' ||
			c == 'O' || c == 'X' || c == 'U')
		unumber(ap, flags, c);
	if (c == 'p')
		pointer(va_arg(ap, void *), flags);
	if (c == 'b' || c == 'B')
		binary(va_arg(ap, long long), flags);
	if (c == 'n')
		;
}

int			printer(char const *fmt, va_list ap, t_flags *flags)
{
	flags->total = 0;
	while (*fmt)
	{
		init_flags(flags);
		if (*fmt == '%' && fmt++)
		{
			set_flags(fmt, flags);
			while (*fmt && !ft_isalpha(*fmt) && *fmt != '%')
				fmt++;
			set_mod_flags(fmt, flags);
			while (*fmt && ft_ismodflag(*fmt))
				fmt++;
			specifier(*fmt, ap, flags);
		}
		else
		{
			write(1, fmt, 1);
			flags->total += 1;
		}
		fmt++;
	}
	return (flags->total);
}

int		ft_printf(const char *fmt, ...)
{
	va_list ap;
	t_flags *flags;
	int		total;

	total = 0;
	flags = (t_flags *)malloc(sizeof(t_flags));
	va_start(ap, fmt);
	init_flags(flags);
	total = printer(fmt, ap, flags);
	free(flags);
	va_end(ap);
	return (total);
}
