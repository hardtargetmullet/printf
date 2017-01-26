/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:56:46 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 02:50:38 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static void	set_mod_flags(char const *fmt, t_flags *flags)
{
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

static void	set_bytes(int *n, t_flags *flags)
{
	*n = flags->total;
}

static void	specifier(char c, va_list ap, t_flags *flags)
{
	if (c == '%')
		char_print('%', flags);
	if (c == 'c' || c == 'C')
		characters(ap, flags, c);
	if (c == 's' || c == 'S')
		string(ap, flags, c);
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
		set_bytes(va_arg(ap, int *), flags);
}

int			printer(char const *fmt, va_list ap, t_flags *flags)
{
	flags->total = 0;
	while (*fmt)
	{
		init_flags(flags);
		if (*fmt == '%' && fmt++)
		{
			if (*fmt == '\0')
				break ;
			set_flags(fmt, flags, ap);
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

int			ft_printf(const char *fmt, ...)
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
