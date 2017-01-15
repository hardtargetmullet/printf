/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:36:37 by anieto            #+#    #+#             */
/*   Updated: 2016/09/27 15:44:25 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	if (!p)
		return (NULL);
	while (i < size)
	{
		p[i] = '\0';
		i++;
	}
	p[i] = '\0';
	return (p);
}
