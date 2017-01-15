/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 21:41:23 by anieto            #+#    #+#             */
/*   Updated: 2016/09/27 22:04:41 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = (unsigned int)ft_strlen(s);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = f(i, (char)s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
