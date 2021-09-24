/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:54:12 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 12:05:30 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;
	size_t		i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		if (*(ptr + i) == (char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
