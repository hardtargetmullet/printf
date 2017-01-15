/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:59:46 by anieto            #+#    #+#             */
/*   Updated: 2016/09/26 23:11:40 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*b;

	i = 0;
	p = (unsigned char *)dst;
	b = (unsigned char *)src;
	while (i < n)
	{
		p[i] = b[i];
		if (b[i] == (unsigned char)c)
			return (p + i + 1);
		i++;
	}
	return (0);
}
