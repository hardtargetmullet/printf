/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <anieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 20:51:33 by anieto            #+#    #+#             */
/*   Updated: 2017/01/13 08:58:54 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

static	int	num_size(unsigned long long num)
{
	int len;

	len = 0;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static int num_size_base(unsigned long long num, int base)
{
	int len;

	len = 0;
	while (num)
	{
		num /= base;
		len++;
	}
	return (len);
}

char		*ft_otoa(unsigned long long n)
{
	char				*p;
	size_t				i;
	unsigned long long	x;

	p = 0;
	x = n;
	if (n == 0)
		return (ft_strdup("0"));
	i = num_size_base(x, 8);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	p[i] = '\0';
	while (x != 0)
	{
		p[--i] = (x % 8) + '0';
		x /= 8;
	}
	return (p);
}

char		*ft_utoa(unsigned long long n)
{
	char			*p;
	size_t			i;
	unsigned long long x;

	p = 0;
	x = n;
	if (n == 0)
		return (ft_strdup("0"));
	i = num_size_base(x, 10);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	p[i] = '\0';
	while (x != 0)
	{
		p[--i] = (x % 10) + '0';
		x /= 10;
	}
	return (p);
}

char *ft_itoa_base(int value, int base)
{
	char	*p;
	char	*b = "0123456789abcdef";
	long	n;
	int		len;

	n = value;
	len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	/*
	while (n)
	{
		n = n / base;
		len++;
	}*/
	len = num_size(n);
	n = value;
	if (n < 0)
	{
		if (base == 10)
			len++;
		n *= -1;
	}
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
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

char *ft_utoa_base(unsigned long long value, int base, int lc)
{
	char	*p;
	char	*b;
	unsigned long long	n;
	int		len;

	if (lc == 1)
		b = "0123456789abcdef";
	else
		b = "0123456789ABCDEF";
	n = value;
	len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	len = num_size_base(n, 16);
	n = value;
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	while (n)
	{
		p[--len] = b[n % base];
		n /= base;
	}
	return (p);
}

char *ft_ltoa_base(long value, int base)
{
	char	*p;
	char	*b = "0123456789abcdef";
	long	n;
	int		len;

	n = value;
	len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	while (n)
	{
		n = n/base;
		len++;
	}
	n = value;
	if (n < 0)
	{
		if (base == 10)
			len++;
		n *= -1;
	}
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
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
