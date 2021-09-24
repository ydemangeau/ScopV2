/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:55:38 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 12:15:41 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptrdest;
	char	*ptrsrc;
	size_t	i;

	ptrdest = (char *)dest;
	ptrsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		*(ptrdest + i) = *(ptrsrc + i);
		i++;
	}
	return (dest);
}
