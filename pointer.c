/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:09:28 by anieto            #+#    #+#             */
/*   Updated: 2017/01/14 16:47:47 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static int	spaces(int size, t_flags *flags)
{
	int i;
	
	i = 0;
	while (i + size < flags->field_width - 2)
	{
		ft_putchar(' ');
		i++;
	}
	return (0);
}

void	pointer(void *v, t_flags *flags)
{
	long	num;
	int 	size;
	char	*p;

	num = (long)v;
	p = ft_ltoa_base(num, 16);
	size = ft_strlen(p);
	if (flags->neg_sign)
	{
		ft_putstr("0x");
		ft_putstr(p);
	}
	if (flags->field_width > size)
		spaces(size, flags);
	if (!flags->neg_sign)
	{
		ft_putstr("0x");
		ft_putstr(p);
	}
}
