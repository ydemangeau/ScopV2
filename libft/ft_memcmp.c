/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:54:58 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 12:05:48 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ptr1;
	const unsigned char *ptr2;
	size_t				i;

	ptr1 = (unsigned char*)s1;
	ptr2 = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (*(ptr1 + i) - *(ptr2 + i) == 0)
			i++;
		else
		{
			return (*(ptr1 + i) - *(ptr2 + i));
		}
	}
	return (0);
}
