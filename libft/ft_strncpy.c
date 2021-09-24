/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:21:23 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 15:22:03 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int i;
	unsigned int in;

	in = n;
	i = 0;
	if (n > 2147483647)
		return (0);
	while (src[i] != '\0' && n--)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < in)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
