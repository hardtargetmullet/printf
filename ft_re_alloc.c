/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 06:53:02 by anieto            #+#    #+#             */
/*   Updated: 2017/01/26 06:53:42 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libftprintf.h"

char	*ft_re_alloc(char *str, size_t size)
{
	char	*p;
	size_t	i;

	p = NULL;
	i = 0;
	if (str)
	{
		p = (char *)malloc(sizeof(char) * (size));
		if (!p)
			return (NULL);
		ft_bzero(p, size);
		ft_strcpy(p, str);
		free(str);
		str = NULL;
	}
	return (p);
}
