/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:20:40 by anieto            #+#    #+#             */
/*   Updated: 2016/11/10 21:31:00 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*b;

	i = 0;
	p = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
		{
			p[len] = b[len];
		}
	}
	return (dst);
}
