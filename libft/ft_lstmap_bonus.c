/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:33:49 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/18 00:55:11 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*new;
	t_list	*first;

	elem = lst;
	if (!elem || !f)
		return (NULL);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->content = (*f)(elem->content);
	first = new;
	while (elem->next != 0)
	{
		elem = elem->next;
		if (!(new->next = (t_list *)malloc(sizeof(t_list))))
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new = new->next;
		new->content = (*f)(elem->content);
	}
	return (first);
}
