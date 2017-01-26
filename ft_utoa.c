/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 20:51:33 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 00:22:38 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static int	num_size_long(long long num, int base)
{
	int len;

	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

char		*ft_ltoa_base(long long value, int base)
{
	char		*p;
	char		*b;
	long long	n;
	int			len;

	n = value;
	b = "0123456789abcdef";
	if (n == 0)
		return (ft_strdup("0"));
	len = num_size_long(n, 2);
	if (n < 0 && base == 10)
		len++;
	if (n < 0)
		n *= -1;
	if (!(p = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	p[len] = '\0';
	while (n)
	{
		p[--len] = b[n % base];
		n /= base;
	}
	if (value < 0 && base == 10)
		p[0] = '-';
	return (p);
}
