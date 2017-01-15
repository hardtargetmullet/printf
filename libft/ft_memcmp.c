/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 05:30:33 by anieto            #+#    #+#             */
/*   Updated: 2016/09/27 05:43:03 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*p;
	char	*d;

	i = 0;
	p = (char *)s1;
	d = (char *)s2;
	while (i < n)
	{
		if (*p != *d)
			return ((unsigned char)*p - (unsigned char)*d);
		i++;
		p++;
		d++;
	}
	return (0);
}
