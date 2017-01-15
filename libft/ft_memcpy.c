/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:58:15 by anieto            #+#    #+#             */
/*   Updated: 2016/09/26 18:05:49 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*b;

	i = 0;
	p = (char *)dst;
	b = (char *)src;
	while (i < n)
	{
		p[i] = b[i];
		i++;
	}
	return (dst);
}
