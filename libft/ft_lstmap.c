/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 03:24:36 by anieto            #+#    #+#             */
/*   Updated: 2016/10/03 19:46:35 by anieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *ret;
	t_list *tmpres;
	t_list *tmplst;

	if (lst == NULL || f == NULL)
		return (NULL);
	tmplst = f(lst);
	ret = ft_lstnew(tmplst->content, tmplst->content_size);
	if (ret)
	{
		tmpres = ret;
		lst = lst->next;
		while (lst != NULL)
		{
			tmplst = f(lst);
			if (!(tmpres->next = ft_lstnew(tmplst->content,
				tmplst->content_size)))
				return (NULL);
			tmpres = tmpres->next;
			lst = lst->next;
		}
	}
	return (ret);
}
