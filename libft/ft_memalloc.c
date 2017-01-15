/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:23:56 by anieto            #+#    #+#             */
/*   Updated: 2016/09/27 14:59:37 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(sizeof(char) * size);
	if (!p)
		return (NULL);
	while (i < size)
	{
		p[i] = '\0';
		i++;
	}
	return ((void *)p);
}
