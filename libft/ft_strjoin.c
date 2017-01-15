/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 01:30:10 by anieto            #+#    #+#             */
/*   Updated: 2016/09/28 02:03:52 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		p = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!p)
			return (NULL);
		while (s1[++i] != '\0')
			p[i] = s1[i];
		while (s2[++j] != '\0')
			p[i++] = s2[j];
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}
