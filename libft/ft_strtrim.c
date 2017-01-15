/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 02:15:35 by anieto            #+#    #+#             */
/*   Updated: 2016/10/03 19:54:14 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	l;
	char	*temp;

	i = 0;
	if (!s)
		return (NULL);
	l = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	l = ft_strlen(&s[i]) - 1;
	while (s[i] && (s[l + i] == ' ' || s[l + i] == '\t' || s[l + i] == '\n'))
		l--;
	temp = ft_strnew(l + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, s + i, l + 1);
	return (temp);
}
