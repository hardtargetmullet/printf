/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 01:44:56 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 02:51:45 by anieto           ###   ########.fr       */
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
	flags->width = 0;
	flags->precision = 0;
	flags->pre_amount = 0;
	flags->h_mod = 0;
	flags->hh_mod = 0;
	flags->l_mod = 0;
	flags->ll_mod = 0;
	flags->j_mod = 0;
	flags->z_mod = 0;
}

void	spaces(int n, t_flags *flags, int c)
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

int		ft_ismodflag(int c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		num_size(uintmax_t num, int base)
{
	int len;

	len = 1;
	while (num /= base)
	{
		len++;
	}
	return (len);
}

char	*ft_capitalize(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
	return (str);
}
