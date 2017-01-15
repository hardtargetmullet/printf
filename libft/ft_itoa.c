/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 20:34:14 by anieto            #+#    #+#             */
/*   Updated: 2016/09/29 06:37:22 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	num_size(int num)
{
	int len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	rev_str(char *p)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(p) - 1;
	if (p[0] == '-')
		i++;
	while (i < j)
	{
		c = p[i];
		p[i] = p[j];
		p[j] = c;
		i++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char	*p;
	size_t	i;

	p = 0;
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	p = (char *)malloc(sizeof(char) * (num_size(n) + 1));
	if (!p)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		p[i++] = '-';
	}
	while (n != 0)
	{
		p[i++] = (n % 10) + '0';
		n /= 10;
	}
	p[i] = '\0';
	rev_str(p);
	return (p);
}
