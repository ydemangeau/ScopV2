/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:35:11 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/21 17:34:18 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	tmp = NULL;
	while (list != NULL)
	{
		if (list->next != NULL)
			tmp = list->next;
		else
			tmp = NULL;
		del(list->content, list->content_size);
		ft_memdel((void *)alst);
		list = tmp;
		free(tmp);
	}
	*alst = NULL;
}
